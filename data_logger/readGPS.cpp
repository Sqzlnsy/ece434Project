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
#define ERROR_ALIGN 

double data_gps[7];
double data_imu[6];

struct flock lock;
struct itimerspec its;
struct gps_data_t gps_d;
char buffer[1024];
size_t buffer_size = sizeof(buffer);
int counter = 0;


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
        FILE *fo = fopen("gyroL.log", "a+");
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
            double sec = tv.tv_sec;
            double usec = tv.tv_usec/1000000.0;
            double time = sec + usec;
            fprintf(fo, "%lf %lf %lf %lf %lf %lf %lf\n"
                        ,time, data_imu[0],data_imu[1],data_imu[2],data_imu[3],data_imu[4],data_imu[5]);
            if(counter%100==0)
            printf("x_speed: %lf y_speed:%lf z_speed:%lf\n x_accel:%lf y_accel:%lf z_accel:%lf\n",
                    data_imu[3],data_imu[4],data_imu[5],data_imu[0],data_imu[1],data_imu[2]);

            fclose(fo);

    return 0;
}

void* clear_file(void* ignore){
    FILE *fo = fopen("gpsL.log", "w");
    FILE *fg = fopen("gyroL.log", "w");
    fprintf(fo, "");
    fprintf(fg, "");
    fclose(fo);
    fclose(fg);
    return 0;
}
void* write_gps_file(void* ignor) {
    // Create the timer
    int i =0;
    // Set the gpsd daemon to streaming mode
    FILE *fo = fopen("gpsL.log", "a+");

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
            double sec = tv.tv_sec;
            double usec = tv.tv_usec/1000000.0;
            double time = sec + usec;

            double latitude = 0;
            double longitude = 0;
            double altitude = 0;
            double speed =0;
            double track =0;
            latitude =latitude+ gps_d.fix.latitude;
            longitude =longitude+ gps_d.fix.longitude;
            altitude =altitude+ gps_d.fix.altHAE;
            track = track+gps_d.fix.track;//angle
            if(!(track>=-360) || !(track<=360)){
                track = 0;
            }
            double climb = gps_d.fix.climb;
            double dx_speed = gps_d.fix.NED.velE;
            double nb_speed = gps_d.fix.NED.velN;



            data_gps[0] = latitude;
            data_gps[1] = longitude;
            data_gps[2] = altitude;
            data_gps[3] = track;
            data_gps[4] = climb;
            data_gps[5] = dx_speed;
            data_gps[6] = nb_speed;


            
            fprintf(fo, "%lf %lf %lf %lf %lf %lf %lf\n"
                        ,time,data_gps[0],data_gps[1] ,data_gps[2] ,data_gps[3] ,data_gps[4] ,data_gps[5],data_gps[6] );
            if(counter%100==0)
            printf("latitude:%lf longitude:%lf altitude:%lf\n track:%lf climb:%lf dx_speed:%lf nb_speed:%lf\n",
                        data_gps[0],data_gps[1] ,data_gps[2] ,data_gps[3] ,data_gps[4] ,data_gps[5],data_gps[6]);
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

    FILE *scale_Accel = fopen("/sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/in_accel_scale","r");
    FILE *scale_Angle = fopen("/sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/in_anglvel_scale","r");
    double accel_scale,angle_scale; 
    fscanf(scale_Accel, "%lf", &accel_scale);
    fscanf(scale_Angle, "%lf", &angle_scale);

    int count = 0;
    clear_file(0);
    struct timeval tv;
    double start_time,now_time,delay_time;
    double sleep_time=0;

    while(1){
        gettimeofday(&tv, NULL);
        start_time =tv.tv_sec + tv.tv_usec/1000000.0;
        printf("%f\n",start_time);
        counter++;
        count += 1;
        if (count % (FREQUENCY_GYRO/FREQUENCY)==0){
            write_gps_file(0);
        }
        gyro_read(accel_scale,angle_scale);

        write_gyro(0);

        gettimeofday(&tv, NULL);

        now_time = tv.tv_sec + tv.tv_usec/1000000.0;
        printf("%f\n",now_time);

        delay_time = now_time - start_time;
                    //    printf("%f\n",delay_time);
        printf("%f\n",(delay_time*1000000.0));

        sleep_time = (1000000)/FREQUENCY_GYRO-(delay_time*1000000.0);

        usleep(sleep_time);

        // read_file(0);
        if(counter >= 1600){
            break;
        }

    }



}