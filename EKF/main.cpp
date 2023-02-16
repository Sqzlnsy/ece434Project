#include <stdio.h>
#include <stdlib.h>
#include <sys/timerfd.h>
#include <unistd.h>
#include "EKalmanGND.h"
#include "insfilterNonholonomic.h"
#include "quaternion.h"
#include "rt_nonfinite.h"
#include "vectorBuffer.h"

#define IMU_BUFFER_SIZE 160
#define GPS_BUFFER_SIZE 10
#define FREQUENCY_GYRO 160
#define STATE_BUFFER_SIZE 200
#define FREQUENCY 10
#define TEST


Queue *accel = createQueue(IMU_BUFFER_SIZE);
Queue *gyro = createQueue(IMU_BUFFER_SIZE);
Queue *gpsPos = createQueue(GPS_BUFFER_SIZE);
Queue *gpsVel = createQueue(GPS_BUFFER_SIZE);
Queue *position = createQueue(STATE_BUFFER_SIZE);
uint EKF_counter = 0;
bool thread_ctl = 0;

//  Acquire the current estimate of the filter states
void getPos(EKalmanGND obj, vector_t *p);
void getOri(EKalmanGND obj, coder::quaternion *f);
void getVel(EKalmanGND obj, vector_t *v);

const double b_initstate[16]={
     0.707102158190293,0,0,0.707111404152578,
    0,0,0,15.3984387870298,0.0420983831777497,0,
    -3.45022754854589,6.73654229572201,0,0,0,0};
const double Rnoise[2]={1, 0.01};
const double Qnoise[4]={0.00400000000000000, 4.00000000000000E-10,	2,	0.000200000000000000};
const double zVCst=0.1;
int skip = 5;
int count = 1000;

int main(int, char **)
{
    EKalmanGND obj;
    coder::insfilterNonholonomic lobj_0;
    double imuFs=160, gpsFs=10;
    double localOrigin[3];
    vector_t v = rear(gpsPos);
    int fileIndicator = 0;
    #ifdef TEST
    int i=0, j=0;
    FILE *fpa = fopen("accel.txt", "r");
    if (fpa == NULL) {
        printf("Cannot open accel.txt");
    }
    FILE *fpg = fopen("gyro.txt", "r");
    if (fpg == NULL) {
        printf("Cannot open gyro.txt");
    }
    FILE *fpl = fopen("lla.txt", "r");
    if (fpl == NULL) {
        printf("Cannot open lla.txt");
    }
    FILE *fpv = fopen("gpsvel.txt", "r");
    if (fpv == NULL) {
        printf("Cannot open gpsvel.txt");
    }
    v.x = 42.2825000000000;
    v.y = -71.3430000000000;
    v.z = 53.0352000000000;
    #endif
    localOrigin[0] = v.x;
    localOrigin[1] = v.y;
    localOrigin[3] = v.z;
    obj.init(b_initstate, imuFs, Rnoise, Qnoise, zVCst, localOrigin, &lobj_0);
    // Loop setup
    double acc[3], gyr[3], lla[3], gpsv[3], pos[3];
    int writectl = 0;
    FILE *fp;
    while(1){
        #ifdef TEST
        if(skip>0){
            skip--;
            for(j=0;j<FREQUENCY_GYRO/FREQUENCY;j++){
                vector_t a;
                fscanf(fpa, "%lf", &(a.x));
                fscanf(fpa, "%lf", &(a.y));
                fscanf(fpa, "%lf", &(a.z));
                a.ts = 10;
                vector_t g;
                fscanf(fpg, "%lf", &(g.x));
                fscanf(fpg, "%lf", &(g.y));
                fscanf(fpg, "%lf", &(g.z));
                g.ts = 10;
                enqueue(accel, a);
                enqueue(gyro, g);
            }
            vector_t p;
            fscanf(fpl, "%lf", &(p.x));
            fscanf(fpl, "%lf", &(p.y));
            fscanf(fpl, "%lf", &(p.z));
            p.ts = 10;
            vector_t v;
            fscanf(fpv, "%lf", &(v.x));
            fscanf(fpv, "%lf", &(v.y));
            fscanf(fpv, "%lf", &(v.z));
            v.ts = 10;
            enqueue(gpsPos, p);
            enqueue(gpsVel, v);
            //printQueue(accel);
            //printf("\n");
        }
        if(isEmpty(gpsPos) && isEmpty(gpsVel) && isEmpty(accel) && isEmpty(gyro) && isEmpty(position)){
            break;
        }
        #endif
        if(isFull(gpsPos) || isFull(gpsVel)){
            printf("GPS buffer is full!!\n");
        }
         if(isFull(accel) || isFull(gyro)){
            printf("IMU buffer is full!!\n");
        }
        if(EKF_counter==0){
            if(!(isEmpty(gpsPos) && isEmpty(gpsVel))){
                vector_t v = dequeue(gpsPos);
                lla[0] = v.x;
                lla[1] = v.y;
                lla[2] = v.z;
                v = dequeue(gpsVel);
                gpsv[0] = v.x;
                gpsv[1] = v.y;
                gpsv[3] = v.z;
                obj.updateGPS(lla, gpsv);
                EKF_counter++;
                EKF_counter%= uint(FREQUENCY_GYRO/FREQUENCY+1);
                writectl = 0;
                if(fileIndicator){
                    fclose(fp);
                    fileIndicator = 0;
                }
                getPos(obj, &v);
                enqueue(position, v);
            } else{
                writectl = 1;
                if(!fileIndicator){
                    fp = fopen("position.txt", "w");
                    fileIndicator = 1;
                    if (fp == NULL) {
                    printf("Cannot open position.txt\n");
                        break;
                    }
                }
                
            }
        }else {
            if(!(isEmpty(accel) && isEmpty(gyro))){
                vector_t v = dequeue(accel);
                acc[0] = v.x;
                acc[1] = v.y;
                acc[2] = v.z;
                v = dequeue(gyro);
                gyr[0] = v.x;
                gyr[1] = v.y;
                gyr[2] = v.z;
                obj.updateIMU(acc, gyr);
                EKF_counter++;
                EKF_counter%= uint(FREQUENCY_GYRO/FREQUENCY+1);
                writectl = 0;
                if(fileIndicator){
                    fclose(fp);
                    fileIndicator = 0;
                }
                getPos(obj, &v);
                enqueue(position, v);
            }else{
                writectl = 1;
                 if(!fileIndicator){
                    fp = fopen("position.txt", "w");
                    fileIndicator = 1;
                    if (fp == NULL) {
                        printf("Cannot open position.txt\n");
                        break;
                    }
                }
            }
        }
        if(writectl){
            //printQueue(position);
            if(!isEmpty(position)){
                vector_t v = dequeue(position);
                fprintf(fp, "%lf %lf %lf %lf\n", v.ts, v.x, v.y, v.z);
                printf("%lf %lf %lf %lf\n", v.ts, v.x, v.y, v.z);
            }
        }
    }
    fclose(fpa);
    fclose(fpg);
    fclose(fpl);
    fclose(fpv);
    if(fileIndicator) fclose(fp);
}

void getVel(EKalmanGND obj, vector_t *v){
    v->x = obj.gndFusion->pState[10];
    v->y = obj.gndFusion->pState[11];
    v->z = obj.gndFusion->pState[12];
}

void getPos(EKalmanGND obj, vector_t *p){
    p->x = obj.gndFusion->pState[7];
    p->y = obj.gndFusion->pState[8];
    p->z = obj.gndFusion->pState[9];
}
void getOri(EKalmanGND obj, coder::quaternion *f){
    f->a = obj.gndFusion->pState[0];
    f->b = obj.gndFusion->pState[1];
    f->c = obj.gndFusion->pState[2];
    f->d = obj.gndFusion->pState[3];
}
