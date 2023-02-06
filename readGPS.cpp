#include <stdio.h>
#include <stdlib.h>
#include <sys/timerfd.h>
#include <unistd.h>
#include <gps.h>
#include <pthread.h>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *writeToFile(void *arg)
{
    int fd;
    float *data = (float *)arg;
    int dataLength = *(int *) (arg + sizeof(float) * 100);
    char filename[] = "gps_data.txt";

    while (1)
    {
        // Lock the mutex
        pthread_mutex_lock(&lock);

        // Wait for a signal from the main thread
        pthread_cond_wait(&cond, &lock);

        fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
        if (fd == -1)
        {
            perror("Error opening file");
        }
        else
        {
            for (int i = 0; i < dataLength; i++)
            {
                char buffer[32];
                sprintf(buffer, "%.2f\n", data[i]);
                write(fd, buffer, strlen(buffer));
            }
        }
        close(fd);

        // Unlock the mutex
        pthread_mutex_unlock(&lock);
    }

    pthread_exit(NULL);
}

int main() {
    int fd;
    struct itimerspec its;
    u_int64_t exp, tot_exp;
    struct gps_data_t gps_data;
    char buffer[1024];
    size_t buffer_size = sizeof(buffer);

    // Connect to the gpsd daemon
    int gps_fd = gps_open("localhost", "2947", &gps_data);
    if (gps_fd == -1) {
        // Error connecting to gpsd
        return 1;
    }
    gps_stream(&gps_data, WATCH_ENABLE | WATCH_JSON, NULL);
    sleep(2);

    // Create the timer
    fd = timerfd_create(CLOCK_MONOTONIC, 0);
    if (fd == -1) {
        perror("timerfd_create");
        return 1;
    }

    // Set the timer to expire after 0.1 second
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 100000000;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 100000000;

    // Start the timer
    if (timerfd_settime(fd, 0, &its, NULL) == -1) {
        perror("timerfd_settime");
        return 1;
    }

    // Set the gpsd daemon to streaming mode
    FILE *fo = fopen("gpsL.log", "w");
    if (fo == NULL) {
        printf("Cannot open output.txt");
    }
    // Read the timer values
    tot_exp=0;
    while (read(fd, &exp, sizeof(u_int64_t)) > 0) {
        tot_exp += exp;
        // Sample the data here
        // Get the current GPS position
        if (gps_read(&gps_data, buffer, buffer_size) == -1) {
            // Error reading GPS data
            return 1;
        }
        fprintf(fo, "%lf %lf %lf\n", gps_data.fix.latitude, gps_data.fix.longitude, gps_data.fix.altitude);
        if (tot_exp >= 200){
            break;
        }
    }

    return 0;
}
