#ifndef DRONEDELIVERYSYSTEM_WEATHER_HPP
#define DRONEDELIVERYSYSTEM_WEATHER_HPP

#include <sys/param.h>
#include <pthread.h>
#define MAX_WIND 5
#define WEATHER_SLEEP 2 + rand() % 8

/* Global variable accesible by threads and its mutex*/
int wind ;
pthread_mutex_t mutexWind;

pthread_t initWeather(void);
void *changeWeather(void *data);

#endif //DRONEDELIVERYSYSTEM_WEATHER_HPP
