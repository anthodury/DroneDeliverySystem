#include "Weather.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *changeWeather(void *data)
{
    while(1){
        // Change weather
        // Notify drone and others ...
        printf("Weather changed\n");
        unsigned int timeWaiting=3+rand()%30;
        sleep(timeWaiting);
    }
}

pthread_t initWeather(void){
    pthread_t threadWeather;
    if (pthread_create(&threadWeather, 0, changeWeather,NULL)){
        printf("error creating thread weather");
    }
    return threadWeather;
}
