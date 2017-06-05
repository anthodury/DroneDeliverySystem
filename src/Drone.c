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

int canDeliver2(Drone* drone, Client *arrayClient[], int size) {
	int cost, distanceMax=0;
	for(int i=0;i<size;++i){
		int currentDistance=arrayClient[i]->distance;
		cost+=currentDistance * arrayClient[i]->command->weight;

		if(distanceMax < currentDistance) distanceMax=currentDistance;
	}
	cost+=2 * distanceMax * (MAX_WIND+MOVE_BATTERY_COST);

	return drone->currentBattery > cost;
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

	if(targetAndClientPresent(client)){
		printf("Ready for delivery\n");
		/**
         * Remove from Slot
         * TO COMPLETE
         */
	}

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
/*
 * TODO with multiple clients
void  deliver2(Drone* drone, Client* client / Client * client []) {

}
 */

int targetAndClientPresent(Client* client){
	int targetPresent=0;
	//Wait 10 secondes max before leave if target is not present
	for(int i=0;i<10;++i){
		if(hasTarget(client) ){
			targetPresent=1;
			printf("OK, target is present\n");
			break;
		}
		//printf("Target is not present. Will leave if no target in %d seconds\n",10-i);
		sleep(1);
	}

	if(!targetPresent)
		printf("Target Absent ! \n");

	int clientPresent=0;
	if(targetPresent){
		//Wait 30 secondes max before leave if client is not present
		for(int i=0;i<30;++i){
			if(isPresent(client)){
				clientPresent=1;
				printf("OK, client is present\n");
				break;
			}
			//printf("Client is not present. Will leave if no client in %d seconds\n",30-i);
			sleep(1);
		}
	}
	if(!clientPresent)
		printf("Client Absent  !\n");

	return (clientPresent && targetPresent);
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
			//TODO : deliver With multiple clients
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

