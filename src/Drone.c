#include <Client.h>
#include <Drone.h>
#include <Weather.h>
#include <TrafficLanes.h>
#include <time.h>
#include <MotherShip.h>


Drone createDrone() {
	return (Drone) {MAX_BATTERY,MAX_BATTERY,Available};
}

int canDeliver(Drone* drone, Client* client) {
	return drone->currentBattery > 2 * client->distance * (client->command->weight - MAX_WIND - MOVE_BATTERY_COST);
}

void  deliver(Drone* drone, Client* client) {
	/* going to the client*/
	for(int i = 0 ; i < client->distance; ++i) {
		pthread_mutex_lock(&mutexLanes[client->trafficLane][0]);
		move(drone,client);
		sleep(1);
		pthread_mutex_unlock(&mutexLanes[client->trafficLane][0]);
		printf("Drone %li going %d\n",(int) pthread_self(),i);
	}

	printf("DRONE  ARRIVED TO CLIENT HOUSE  BATTERY : %d\n",drone->currentBattery);

	/**
	 * meet the client or wait him
	 * TO COMPLETE
	 */

	/* go back to the Mother Ship*/
	for(int i = 0 ; i < client->distance; ++i) {
		pthread_mutex_lock(&mutexLanes[client->trafficLane][1]);
		move(drone,client);
		pthread_mutex_unlock(&mutexLanes[client->trafficLane][1]);
		printf("Drone going back %d\n",i);
		sleep(1);
	}
}

void move(Drone* drone , Client* client) {
	pthread_mutex_lock(&mutexWind);
	drone->currentBattery -= wind;
	pthread_mutex_unlock(&mutexWind);
	drone->currentBattery -= client->command->weight - MOVE_BATTERY_COST;
}

void * run (void * data) {
	srand(time(NULL));
	Drone drone = createDrone();
	recharge(&drone);
	Client client = createClient();
	deliver(&drone,&client);
	freeClient(&client);
}

pthread_t initDrone () {
	pthread_t threadDrone;
	pthread_create(&threadDrone,NULL,run,NULL);
}
