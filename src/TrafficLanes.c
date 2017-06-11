#include <TrafficLanes.h>

void initLanesMutex()  {
	for (int i= 0 ;i < MAX_TRAFFIC_LANES ; ++i) {
		for(int k = 0; k < MAX_DISTANCE; ++k) {
			pthread_mutex_init(&mutexLanes[i][k][0], NULL);
			pthread_mutex_init(&mutexLanes[i][k][1], NULL);
		}
	}
}