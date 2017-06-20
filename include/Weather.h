#ifndef DRONEDELIVERYSYSTEM_WEATHER_HPP
#define DRONEDELIVERYSYSTEM_WEATHER_HPP

#include <pthread.h>
#define MAX_WIND 5
#define WEATHER_SLEEP 2 + rand() % 8

/* Global variable accesible by threads and its mutex*/
int wind ;
pthread_mutex_t mutexWind;

/*------------------------------------------------------------------------*//**
 * @brief      Initializes the weather's thread.
 *
 * @return     The weather's thread.
 */
pthread_t initWeather(void);

/*------------------------------------------------------------------------*//**
 * @brief      The function of the weather's thread
 *
 * @param[in]  data Not used
 */
void *changeWeather(void *data);

#endif //DRONEDELIVERYSYSTEM_WEATHER_HPP
