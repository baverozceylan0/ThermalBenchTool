#define MAX_LEN 256 //For the string buffers 
#define MAX_THERMALZONE_NUMBER 10
#define THERMALZONE_DIGIT_NUMBER 2 // 2 digit will support 100 thermal zones
#define SLEEP_INTERVAL_FOR_TIMING 100 // in microseconds
#define SLEEP_INTERVAL_FOR_IDLE_TIME_INJECTION 100 // in microseconds

#define TEMPERATURE_SAMPLING_PERIOD 100 // in miliseconds
#define TEMPERATURE_LOG_PERIOD 1 // in seconds

#define UTIL_SAMPLING_PERIOD 200 // in miliseconds

#define FREQ_SAMPLING_PERIOD 100 // in miliseconds



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

long millis(){
    struct timespec _t;
    clock_gettime(CLOCK_REALTIME, &_t);
    return _t.tv_sec*1000 + lround(_t.tv_nsec/1e6);
}

long nanos(){
    struct timespec _t;
    clock_gettime(CLOCK_REALTIME, &_t);
    return _t.tv_sec*1000*1000 + lround(_t.tv_nsec/1e3);
}
