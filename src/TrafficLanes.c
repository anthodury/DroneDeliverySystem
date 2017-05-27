#include <TrafficLanes.h>

void initLanesMutex()  {
	for (int i= 0 ;i < MAX_TRAFFIC_LANES ; ++i) {
		pthread_mutex_init(&mutexLanes[i][0], NULL);
		pthread_mutex_init(&mutexLanes[i][1], NULL);
	}
}