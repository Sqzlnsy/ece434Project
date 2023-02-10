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
#define FREQUENCY 2
#define FREQUENCY_GYRO 1
#define ERROR_ALIGN 3

double data_gps[8];
double data_imu[6];

struct flock lock;
struct itimerspec its;
struct gps_data_t gps_d;
char buffer[1024];
size_t buffer_size = sizeof(buffer);


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
        FILE *fileZ = fopen("/sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/in_accel_z_raw","r");
        FILE *fileY = fopen("/sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/in_accel_y_raw","r");
        FILE *fileX = fopen("/sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/in_accel_x_raw","r");
        FILE *fileAX = fopen("/sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/in_anglvel_x_raw","r");
        FILE *fileAY = fopen("/sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/in_anglvel_y_raw","r");
        FILE *fileAZ = fopen("/sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/in_anglvel_z_raw","r");

        int numberZ,numberY,numberX;
        int numberAZ,numberAY,numberAX;

        if (!fileZ||!fileY||!fileX) {
            printf("Error opening raw data file\n");
            return;
        }
        fscanf(fileZ, "%d", &numberZ);
        fscanf(fileX, "%d", &numberX);
        fscanf(fileY, "%d", &numberY);

        fscanf(fileAZ, "%d", &numberAZ);
        fscanf(fileAX, "%d", &numberAX);
        fscanf(fileAY, "%d", &numberAY);


        fclose(fileZ);
        fclose(fileY);
        fclose(fileX);
        fclose(fileAX);
        fclose(fileAY);
        fclose(fileAZ);


        data_imu[0] = numberX*accel_scale;
        data_imu[1] = numberY*accel_scale;
        data_imu[2] = numberZ*accel_scale;

        data_imu[3] = numberAX*angle_scale;
        data_imu[4] = numberAY*angle_scale;
        data_imu[5] = numberAZ*angle_scale;

}
void *write_gyro(void* ignore){
        FILE *fo = fopen("gyroL.log", "w");
    // Create the timer
        int i =0;
    // Set the gpsd daemon to streaming mode

        int fde = fileno(fo);
        fcntl(fde, F_SETLKW, &lock);

        if (fo == NULL) {
            perror("Cannot open output.txt");
        }
        
            struct timeval tv;
            gettimeofday(&tv, NULL);

            double time = tv.tv_usec;

            fprintf(fo, "%lf|%lf|%lf|%lf|%lf|%lf|%lf"
                        ,time, data_imu[0],data_imu[1],data_imu[2],data_imu[3],data_imu[4],data_imu[5]);

            fclose(fo);

    return 0;
}


void* write_gps_file(void* ignor) {
    // Create the timer
    int i =0;
    // Set the gpsd daemon to streaming mode
    FILE *fo = fopen("gpsL.log", "w");

    int fde = fileno(fo);
        fcntl(fde, F_SETLKW, &lock);

        if (fo == NULL) {
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
            struct timeval tv;
            gettimeofday(&tv, NULL);
            double latitude = 0;
            double longitude = 0;
            double altitude = 0;
            double speed =0;
            double track =0;
            double time = tv.tv_usec;
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



            data_gps[0] = time;
            data_gps[1] = latitude;
            data_gps[2] = longitude;
            data_gps[3] = altitude;
            data_gps[4] = track;
            data_gps[5] = climb;
            data_gps[6] = dx_speed;
            data_gps[7] = nb_speed;



            fprintf(fo, "%lf|%lf|%lf|%lf|%lf|%lf|%lf"
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
    sleep(2);

    FILE *scale_Accel = fopen("/sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/in_accel_scale","r");
    FILE *scale_Angle = fopen("/sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/in_anglvel_scale","r");

    double accel_scale,angle_scale; 
    fscanf(scale_Accel, "%lf", &accel_scale);
    fscanf(scale_Angle, "%lf", &angle_scale);

    int count = 0;
    while(1){
        count += 1;
        if (count == FREQUENCY/FREQUENCY_GYRO){
            write_gps_file(0);
            count = 0;
        }
        gyro_read(accel_scale,angle_scale);
        write_gyro(0);
        usleep((1000000)/FREQUENCY);
        read_file(0);

    }



}