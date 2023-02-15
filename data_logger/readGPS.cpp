#include <sys/timerfd.h>
#include <gps.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cmath>
#include <math.h>

#define FREQUENCY 10
#define FREQUENCY_GYRO 160
#define ERROR_ALIGN 3
#define MACRO 1000000.0

double data_gps[7];
double data_imu[6];

struct flock lock;
struct itimerspec its;
struct gps_data_t gps_d;
char buffer[1024];
size_t buffer_size = sizeof(buffer);
int counter = 0,a,b;

void* read_file(void* ignore){
    char firstLine[1024];
        FILE *fo = fopen("gpsL.log", "r");
        int fde = fileno(fo);
        fcntl(fde, F_SETLKW, &lock);

        if (fo == NULL) {
            perror("Cannot open file");
            return 0;
        }

        if (fgets(firstLine, sizeof(firstLine), fo) == NULL) {
            printf("ignore line\n");
            fclose(fo);
        }
        else{
            struct timeval tv;
            gettimeofday(&tv, NULL);
            printf("%s\n", firstLine);
            fclose(fo);

        }
    return 0;
}

void gyro_read(double accel_scale,double angle_scale){
        int in_accel_z_raw,in_accel_y_raw,in_accel_x_raw;
        int in_anglvel_z_raw,in_anglvel_y_raw,in_anglvel_x_raw;

        FILE *fileZ = fopen("/sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/in_accel_z_raw","r");
        FILE *fileY = fopen("/sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/in_accel_y_raw","r");
        FILE *fileX = fopen("/sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/in_accel_x_raw","r");
        FILE *fileAX = fopen("/sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/in_anglvel_x_raw","r");
        FILE *fileAY = fopen("/sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/in_anglvel_y_raw","r");
        FILE *fileAZ = fopen("/sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/in_anglvel_z_raw","r");
        if (!fileZ||!fileY||!fileX) {
            printf("Error opening raw data file\n");
            return;
        }
        fscanf(fileZ, "%d", &in_accel_z_raw);
        fscanf(fileX, "%d", &in_accel_x_raw);
        fscanf(fileY, "%d", &in_accel_y_raw);

        fscanf(fileAZ, "%d", &in_anglvel_z_raw);
        fscanf(fileAX, "%d", &in_anglvel_x_raw);
        fscanf(fileAY, "%d", &in_anglvel_y_raw);





        data_imu[0] = in_accel_x_raw*accel_scale;
        data_imu[1] = in_accel_y_raw*accel_scale;
        data_imu[2] = in_accel_z_raw*accel_scale;

        data_imu[3] = in_anglvel_x_raw*angle_scale;
        data_imu[4] = in_anglvel_y_raw*angle_scale;
        data_imu[5] = in_anglvel_z_raw*angle_scale;

        fclose(fileZ);
        fclose(fileY);
        fclose(fileX);
        fclose(fileAX);
        fclose(fileAY);
        fclose(fileAZ);
}

void *write_gyro(void* ignore){
        FILE *fo = fopen("gyroL.log", "a+");
    // Create the timer
        int i =0;
    // Set the gpsd daemon to streaming mode
        FILE *f_gyro = fopen("gyroL.log", "a+");

        int fde = fileno(f_gyro);
        fcntl(fde, F_SETLKW, &lock);

        if (f_gyro == NULL) {
            perror("Cannot open output.txt");
        }
        
            struct timeval tv;
            gettimeofday(&tv, NULL);

            double time = tv.tv_usec;

            fprintf(fo, "%lf|%lf|%lf|%lf|%lf|%lf|%lf\n"
                        ,time, data_imu[0],data_imu[1],data_imu[2],data_imu[3],data_imu[4],data_imu[5]);


        fclose(f_gyro);
    return 0;
}

void* clear_file(void* ignore){
    FILE *fo = fopen("gpsL.log", "w");
    FILE *fg = fopen("gyroL.log", "w");
    fprintf(fk, "");
    fprintf(fg, "");
    fclose(fk);
    fclose(fg);
}

void* write_gps_file(struct timeval timer) {
    // Create the timer
    int i =0;
    // Set the gpsd daemon to streaming mode
    FILE *fo = fopen("gpsL.log", "a+");

    int fde = fileno(f_gps);
        fcntl(fde, F_SETLKW, &lock);

        if (f_gps == NULL) {
            perror("Cannot open output.txt");
        }
        
        // Sample the data here
        // Get the current GPS position
        if (gps_read(&gps_d, buffer, buffer_size) == -1) {
            // Error reading GPS data

            perror("Error reading GPS data\n");
            return 0;
        }
            // printf("waiting to write...\n");
            // struct timeval start, end;
            // gettimeofday(&start, NULL);
            // gettimeofday(&end, NULL);

            double latitude = 0;
            double longitude = 0;
            double altitude = 0;
            double speed =0;
            double track =0;
            latitude =latitude+ gps_d.fix.latitude;
            longitude =longitude+ gps_d.fix.longitude;
            altitude =altitude+ gps_d.fix.altitude;
            speed =speed+ gps_d.fix.speed;
            track = track+gps_d.fix.track;//angle
            if(!(track>=-360) || !(track<=360)){
                track = 0;
            }
            double climb = gps_d.fix.climb;
            double dx_speed = sin(track*M_PI/180.0)*speed;
            double nb_speed = cos(track*M_PI/180.0)*speed;



            data_gps[0] = latitude;
            data_gps[1] = longitude;
            data_gps[2] = altitude;
            data_gps[3] = climb;
            data_gps[4] = dx_speed;
            data_gps[5] = nb_speed;
            gettimeofday(&timer, NULL);
            double sec = timer.tv_sec;
            int usec = timer.tv_usec;
            double us = usec/1000000.0;
            double time = sec + us;
            // printf("%lf\n",time);

            // printf("%lf",data_gps[4]);
            fprintf(f_gps, "%lf %lf %lf %lf %lf %lf %lf\n"
                        ,time,data_gps[0],data_gps[1] ,data_gps[2] ,data_gps[3] ,data_gps[4] ,data_gps[5]);


            fprintf(fo, "%lf|%lf|%lf|%lf|%lf|%lf|%lf\n"
                        ,data_gps[0],data_gps[1] ,data_gps[2] ,data_gps[3] ,data_gps[4] ,data_gps[5],data_gps[6] ,data_gps[7]);

            fclose(fo);



    
    return 0;
}

int main(){

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
        // Connect to the gpsd daemon
    int gps_fd = gps_open("localhost", "2947", &gps_d);
    pthread_t new_thread,new_thread2;
    if (gps_fd == -1) {
        // Error connecting to gpsd
        perror("Error connecting to gpsd\n");
        return 0;
    }
    gps_stream(&gps_d, WATCH_ENABLE | WATCH_JSON, NULL);
    printf("start sleep...\n");
    sleep(1);

    FILE *scale_Accel = fopen("/sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/in_accel_scale","r");
    FILE *scale_Angle = fopen("/sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/in_anglvel_scale","r");
    double accel_scale,angle_scale; 
    fscanf(scale_Accel, "%lf", &accel_scale);
    fscanf(scale_Angle, "%lf", &angle_scale);

    int count = 0;
    clear_file(0);
    struct timeval tv;
    int start_time,now_time,delay_time;
    int sleep_time=0;
    struct timeval overall;
    gettimeofday(&overall, NULL);
    a = overall.tv_sec;
    b = overall.tv_usec;

    while(1){
        gettimeofday(&tv, NULL);
        start_time = tv.tv_usec/1000000.0 + tv.tv_sec;
        counter++;
        count += 1;
        if (count == FREQUENCY_GYRO/FREQUENCY){
            write_gps_file(overall);
            count = 0;
        }
        gyro_read(accel_scale,angle_scale);

        write_gyro(overall);
        //  if(counter==100){
        //     printf("latitude:%lf longitude:%lf altitude:%lf\n track:%lf climb:%lf dx_speed:%lf nb_speed:%lf\n",
        //                 data_gps[0],data_gps[1] ,data_gps[2] ,data_gps[3] ,data_gps[4] ,data_gps[5],data_gps[6]);
        //     printf("x_speed: %lf y_speed:%lf z_speed:%lf\n x_accel:%lf y_accel:%lf z_accel:%lf\n",
        //             data_imu[3],data_imu[4],data_imu[5],data_imu[0],data_imu[1],data_imu[2]);
        //     counter =0;
        // }
        gettimeofday(&tv, NULL);

        now_time = tv.tv_usec/MACRO+tv.tv_sec;

        delay_time = (now_time - start_time)*MACRO;
        // printf("%d shoud:%d\n",delay_time,(1000000)/FREQUENCY_GYRO);
        sleep_time = (MACRO)/FREQUENCY_GYRO-delay_time;
        // printf("%d\n",sleep_time);
        //printf("delay : %lf, sleep = %lf\n",start_time, now_time);
        if(sleep_time>0){
            usleep(sleep_time);
        }
        // read_file(0);

    }
}
