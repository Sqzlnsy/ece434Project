#include <stdio.h>
#include <stdlib.h>
#include <sys/timerfd.h>
#include <unistd.h>
#include <gps.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#define FREQUENCY 10
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
int fd;
struct itimerspec its;
struct gps_data_t gps_d;
char buffer[1024];
size_t buffer_size = sizeof(buffer);
void* read_file(void* ignore){
    char firstLine[1024];

    while(1){
        pthread_mutex_lock(&lock);
        pthread_cond_wait(&cond2,&lock);
        printf("start reading...\n");
        FILE *fo = fopen("gpsL.log", "r");
        if (fo == NULL) {
            perror("Cannot open file");
            return 0;
        }

        if (fgets(firstLine, sizeof(firstLine), fo) == NULL) {
            pthread_mutex_unlock(&lock);
            printf("ignore line\n");
            fclose(fo);

            continue;
        }
        else{
            struct timeval tv;
            gettimeofday(&tv, NULL);
            printf("%s\n", firstLine);
            fclose(fo);
            pthread_mutex_unlock(&lock);
        }
    }
}




void* write_file(void* ignore) {
    // Create the timer
    int i =0;
    // Set the gpsd daemon to streaming mode
    while(1){
    pthread_mutex_lock(&lock);

    FILE *fo = fopen("gpsL.log", "w");
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
        pthread_cond_wait(&cond,&lock);
        // gettimeofday(&end, NULL);
        struct timeval tv;
        gettimeofday(&tv, NULL);

        // printf("start writing...\n");
        fprintf(fo, "%li:%li :%lf %lf %lf\n",tv.tv_sec,tv.tv_usec, gps_d.fix.latitude, gps_d.fix.longitude, gps_d.fix.altitude);
        // printf("%lf %lf %lf\n", gps_d.fix.latitude, gps_d.fix.longitude, gps_d.fix.altitude);
        // long int error_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        // printf("Elapsed time: %li us\n", error_time);
        fclose(fo);

        pthread_cond_signal(&cond2);
        pthread_mutex_unlock(&lock);
    }
    return 0;
}

int main(){
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
    fd = timerfd_create(CLOCK_MONOTONIC, 0);
    if (fd == -1) {
        perror("timerfd_create");
        return 0;
    }

    // Set the timer to expire after 0.1 second
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 100000000;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 100000000;

    // Start the timer
    if (timerfd_settime(fd, 0, &its, NULL) == -1) {
        perror("timerfd_settime");
        return 0;
    }
    printf("thread created...\n");
    pthread_create(&new_thread,NULL,write_file,0);
    sleep(1);
    pthread_create(&new_thread2,NULL,read_file,0);

    while(1){
        usleep((1000000)/FREQUENCY);
        pthread_cond_signal(&cond);
    }



}