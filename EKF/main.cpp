#include <stdio.h>
#include <stdlib.h>
#include <sys/timerfd.h>
#include <unistd.h>
#include "EKalmanGND.h"
#include "insfilterNonholonomic.h"
#include "quaternion.h"
#include "rt_nonfinite.h"

//  Acquire the current estimate of the filter states
void getPos(EKalmanGND obj, double *p);
void getOri(EKalmanGND obj, coder::quaternion *f);
const double b_initstate[16]={
     0.707102158190293,0,0,0.707111404152578,
    0,0,0,15.3984387870298,0.0420983831777497,0,
    -3.45022754854589,6.73654229572201,0,0,0,0};
const double Rnoise[2]={1, 0.01};
const double Qnoise[4]={0.00400000000000000, 4.00000000000000E-10,	2,	0.000200000000000000};
const double zVCst=0.1;
const double localOrigin[3]={42.2825000000000,	-71.3430000000000,	53.0352000000000};

int main(int, char **)
{
    EKalmanGND obj;
    coder::insfilterNonholonomic lobj_0;
    double imuFs=160, gpsFs=10;
    obj.init(b_initstate, imuFs, Rnoise, Qnoise, zVCst, localOrigin, &lobj_0);
    // Loop setup
    int secondsToSimulate = 50; // simulate about 50 seconds
    int numsamples = (int) secondsToSimulate*imuFs;

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
     FILE *fo = fopen("output.txt", "w");
    if (fo == NULL) {
        printf("Cannot open output.txt");
    }

    int fd;
    struct itimerspec its;
    uint32_t exp, tot_exp;

    // Create the timer
    fd = timerfd_create(CLOCK_MONOTONIC, 0);
    if (fd == -1) {
        perror("timerfd_create");
        return 1;
    }

    // Set the timer to expire after 1 second
    its.it_value.tv_sec = 1;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 1;
    its.it_interval.tv_nsec = 0;

    // Start the timer
    if (timerfd_settime(fd, 0, &its, NULL) == -1) {
        perror("timerfd_settime");
        return 1;
    }

    int i=0, j=0;
    double d;
    double accel[3], gyro[3], lla[3], gpsvel[3], pos[3];
    while(i<numsamples){
        for(j=0;j<imuFs/gpsFs;j++){
            read(fd, &exp, sizeof(uint64_t));
            fscanf(fpa, "%lf", &d);
            accel[0]=d;
            fscanf(fpa, "%lf", &d);
            accel[1]=d;
            fscanf(fpa, "%lf", &d);
            accel[2]=d;
            fscanf(fpg, "%lf", &d);
            gyro[0]=d;
            fscanf(fpg, "%lf", &d);
            gyro[1]=d;
            fscanf(fpg, "%lf", &d);
            gyro[2]=d;
            obj.updateIMU(accel, gyro);
            getPos(obj, pos);
            fprintf(fo, "%lf\n", pos[1]);
            i++;
        }
        fscanf(fpl, "%lf", &d);
        lla[0]=d;
        fscanf(fpl, "%lf", &d);
        lla[1]=d;
        fscanf(fpl, "%lf", &d);
        lla[2]=d;
        fscanf(fpv, "%lf", &d);
        gpsvel[0]=d;
        fscanf(fpv, "%lf", &d);
        gpsvel[1]=d;
        fscanf(fpv, "%lf", &d);
        gpsvel[2]=d;
        obj.updateGPS(lla, gpsvel);
    }
    fclose(fpa);
    fclose(fpg);
    fclose(fpl);
    fclose(fpv);
    fclose(fo);
}

void getPos(EKalmanGND obj, double p[]){
    p[0] = obj.gndFusion->pState[7];
    p[1] = obj.gndFusion->pState[8];
    p[2] = obj.gndFusion->pState[9];
}
void getOri(EKalmanGND obj, coder::quaternion *f){
    f->a = obj.gndFusion->pState[0];
    f->b = obj.gndFusion->pState[1];
    f->c = obj.gndFusion->pState[2];
    f->d = obj.gndFusion->pState[3];
}
