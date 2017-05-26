
#ifndef DRONEDELIVERYSYSTEM_WEATHER_HPP
#define DRONEDELIVERYSYSTEM_WEATHER_HPP

#include <sys/param.h>

typedef enum  {Sun,Wind,Rain} Weather;

pthread_t initWeather(void);
void *changeWeather(void *data);

#endif //DRONEDELIVERYSYSTEM_WEATHER_HPP
