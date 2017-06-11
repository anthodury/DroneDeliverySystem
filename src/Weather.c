#include "Weather.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <MotherShip.h>


void *changeWeather(void *data) {
  //  while(message != FINISHED){
    while(1){
	    pthread_mutex_lock(&mutexWind);
	    wind = rand() % MAX_WIND;
	    printf("Wind changed to %d\n",wind);
	    pthread_mutex_unlock(&mutexWind);
	    sleep(WEATHER_SLEEP);
    }
	//return NULL;
}

pthread_t initWeather(void) {
    pthread_t threadWeather;
	pthread_mutex_init(&mutexWind,NULL);
    if (pthread_create(&threadWeather, 0, changeWeather,NULL)){
        printf("error creating thread weather");
    }
    return threadWeather;
}
