#include <Client.h>
#include <Drone.h>
#include <Weather.h>
#include <TrafficLanes.h>
#include <time.h>
#include <MotherShip.h>
#include <Package.h>


// TODO: Make drones deliver multiple clients if possible
Drone createDrone() {
	return (Drone) {MAX_BATTERY,MAX_BATTERY,Available};
}

int canDeliver(Drone* drone, Client* client) {
	return drone->currentBattery > 2 * client->distance * (client->command->weight + MAX_WIND + MOVE_BATTERY_COST);
}

void  deliver(Drone* drone, Client* client) {
	printf("Drone %d delivering Client %p\n",pthread_self(),client);
	drone->state = Moving;

	/* going to the client*/
	for(int i = 0 ; i < client->distance; ++i) {
		pthread_mutex_lock(&mutexLanes[client->trafficLane][0]);
		move(drone,client);
		usleep(100000);
		pthread_mutex_unlock(&mutexLanes[client->trafficLane][0]);
	}

	printf("Drone %d arrived at Client's home  Battery : %d\n",pthread_self(),drone->currentBattery);

	/**
	 * meet the client or wait him
	 * TO COMPLETE
	 */

	/* go back to the Mother Ship*/
	for(int i = 0 ; i < client->distance; ++i) {
		pthread_mutex_lock(&mutexLanes[client->trafficLane][1]);
		move(drone,client);
		usleep(100000);
		pthread_mutex_unlock(&mutexLanes[client->trafficLane][1]);
	}
	drone->state = Available;
	printf("Drone %d arrived at MotherShip  Battery : %d\n",pthread_self(),drone->currentBattery);


}

void move(Drone* drone , Client* client) {
	pthread_mutex_lock(&mutexWind);
	drone->currentBattery -= wind;
	pthread_mutex_unlock(&mutexWind);
	drone->currentBattery -= client->command->weight + MOVE_BATTERY_COST;
}

void * run (void * data) {
	int id = (int) data;
	Drone* drone = drones[id];

	while(1) {
		/* wait for MotherShip to unlock */
		sem_wait(&semDrones[id]);
		if(message) {
			Client* toDeliver = clientToDeliver;
			sem_post(&semSynch);
			deliver(drone, toDeliver);
		}
		else {
			recharge(drone);
		}
	}

}

pthread_t initDrone (int index) {
	pthread_t threadDrone;
	pthread_create(&threadDrone,NULL,run,(void*)index);
}

