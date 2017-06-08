#ifndef DRONEDELIVERYSYSTEM_TRAFFICLANES_H
#define DRONEDELIVERYSYSTEM_TRAFFICLANES_H

#include <pthread.h>

#define MAX_TRAFFIC_LANES 20

/* mutex to make sure Drones don't crash into each other*/
pthread_mutex_t mutexLanes[MAX_TRAFFIC_LANES][2];

void initLanesMutex() ;

#endif //DRONEDELIVERYSYSTEM_TRAFFICLANE_H
