#include <stdio.h>
#include <stdlib.h>
#include <sys/timerfd.h>
#include <unistd.h>
#include "EKalmanGND.h"
#include "insfilterNonholonomic.h"
#include "quaternion.h"
#include "rt_nonfinite.h"
#include "vectorBuffer.h"
#include "pthread.h"
#define IMU_BUFFER_SIZE 160
#define GPS_BUFFER_SIZE 20
#define FREQUENCY_GYRO 160
#define STATE_BUFFER_SIZE 200
#define FREQUENCY 10
// #define TEST

// vector buffers
Queue *accel = createQueue(IMU_BUFFER_SIZE);
Queue *gyro = createQueue(IMU_BUFFER_SIZE);
Queue *gpsPos = createQueue(GPS_BUFFER_SIZE);
Queue *gpsVel = createQueue(GPS_BUFFER_SIZE);
Queue *position = createQueue(STATE_BUFFER_SIZE);

// EKF thread control
uint EKF_counter = 1;

pthread_mutex_t gpslock= PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t imulock= PTHREAD_MUTEX_INITIALIZER;

void getVel(EKalmanGND obj, vector_t *v){
    v->x = obj.gndFusion->pState[10];
    v->y = obj.gndFusion->pState[11];
    v->z = obj.gndFusion->pState[12];
}
void getPos(EKalmanGND obj, vector_t *p){
    p->x = obj.gndFusion->pState[7];
    p->y = obj.gndFusion->pState[8];
    p->z = obj.gndFusion->pState[9];
    // printf("%lf\n", p->z);
}
void getOri(EKalmanGND obj, coder::quaternion *f){
    f->a = obj.gndFusion->pState[0];
    f->b = obj.gndFusion->pState[1];
    f->c = obj.gndFusion->pState[2];
    f->d = obj.gndFusion->pState[3];
}

void *EKF_Test(void *ctrl)
{
    bool *sig = (bool*) ctrl;
    const double b_initstate[16]={
     0.707102158190293,0,0,0.707111404152578,
    0,0,0,15.3984387870298,0.0420983831777497,0,
    -3.45022754854589,6.73654229572201,0,0,0,0};
    const double Rnoise[2]={1, 0.01};
    const double Qnoise[4]={0.00400000000000000, 4.00000000000000E-10,	2,	0.000200000000000000};
    const double zVCst=0.1;
    uint EKF_counter = 0;
    EKalmanGND obj;
    coder::insfilterNonholonomic lobj_0;
    double imuFs=FREQUENCY_GYRO, gpsFs=FREQUENCY;
    double localOrigin[3];
    while(isEmpty(gpsPos));
    vector_t v = rear(gpsPos);
    localOrigin[0] = v.x;
    localOrigin[1] = v.y;
    localOrigin[3] = v.z;
    obj.init(b_initstate, imuFs, Rnoise, Qnoise, zVCst, localOrigin, &lobj_0);
    // Loop setup 
   double acc[3], gyr[3], lla[3], gpsv[3], pos[3];
    FILE *fp;
    while(1){
        bool writectl = sig[0];
        bool thread_ctl = sig[1];
        if(isFull(gpsPos) || isFull(gpsVel)){
            printf("GPS buffer is full!!\n");
            printQueue(gpsVel);
            printQueue(gpsPos);
        }
        if(isFull(accel) || isFull(gyro)){
            printf("IMU buffer is full!!\n");
        }
        if(EKF_counter==0){
            if(!(isEmpty(gpsPos) || isEmpty(gpsVel))){
                pthread_mutex_lock(&gpslock);
                vector_t p = dequeue(gpsPos); // gps postion
                pthread_mutex_unlock(&gpslock);
                lla[0] = p.x;
                lla[1] = p.y;
                lla[2] = p.z;
                pthread_mutex_lock(&gpslock);
                vector_t v = dequeue(gpsVel);
                pthread_mutex_unlock(&gpslock);
                gpsv[0] = v.x;
                gpsv[1] = v.y;
                gpsv[2] = v.z;
                // printf("%lf | %lf | %lf \n", lla[0], lla[1], lla[2]);
                obj.updateGPS(lla, gpsv);   // gps velocity
                EKF_counter++;
                EKF_counter%= uint(FREQUENCY_GYRO/FREQUENCY+1);
                writectl = 0;
                // getPos(obj, &v);
                // enqueue(position, v);
            } else{
                writectl = 1;
            }
        }
        else {
            if(!(isEmpty(accel) || isEmpty(gyro))){
                pthread_mutex_lock(&imulock);
                vector_t v = dequeue(accel);
                pthread_mutex_unlock(&imulock);
                acc[0] = v.x;
                acc[1] = v.y;
                acc[2] = v.z;

                pthread_mutex_lock(&imulock);
                v = dequeue(gyro);
                pthread_mutex_unlock(&imulock);
                gyr[0] = v.x;
                gyr[1] = v.y;
                gyr[2] = v.z;
                //printf("%lf | %lf | %lf \n", acc[0], acc[1], acc[2]);

                obj.updateIMU(acc, gyr);
                EKF_counter++;
                EKF_counter%= uint(FREQUENCY_GYRO/FREQUENCY+1);
                writectl = 0;
                getPos(obj, &v);
                enqueue(position, v);
                //printQueue(position);
                
            }else{
                writectl = 1;
            }
        }
        if(writectl){
            //printQueue(position);
            fp = fopen("position.txt", "a+");
            while(!isEmpty(position)){
                vector_t v = dequeue(position);
                fprintf(fp, "%lf %lf %lf %lf\n", v.ts, v.x, v.y, v.z);
                //printf("%lf %lf %lf %lf\n", v.ts, v.x, v.y, v.z);
            }
            fclose(fp);
        }
        if(!thread_ctl){
            break;
        }
    }
    return 0;
}
