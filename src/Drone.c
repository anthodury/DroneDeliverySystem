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
	int cost = 0, distanceMax=0;
	/* adding weight cost*/
	for(int i=0;i<size;++i){
		int currentDistance=arrayClient[i]->distance;
		cost+=currentDistance * arrayClient[i]->command->weight;

		if(distanceMax < currentDistance) distanceMax=currentDistance;
	}
	// worst case : no clients were present , we count weight cost twice
	cost = 2 * cost ;
	//add wind and move cost
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

void  deliver2(Drone* drone,Client * clients [] , int size) {
	int distance = 0;
	int weight = computeTotalWeight(clients,size);
	int trafficLane = clients[0]->trafficLane;

	//sort clients by  increasing distance
	qsort(clients,size,sizeof(Client*),compareClientsByDistance);
	//printf(" sort : %d %d",clients[0]->distance,clients[1]->distance);

	/* go deliver all clients*/
	for(int i = 0 ; i < size; ++i) {
		for(distance;distance < clients[i]->distance ; ++distance) {
			pthread_mutex_lock(&mutexLanes[trafficLane][0]);
			move2(drone,weight);
			usleep(100000);
			pthread_mutex_unlock(&mutexLanes[trafficLane][0]);
		}
		if(targetAndClientPresent(clients[i])) {
			printf("Ready for delivery\n");
			isDelivered[clients[i]->id] = 1;
			weight -= clients[i]->command->weight;
		}
	}
	printf("Drone %d delivered last Client Battery : %d \n",pthread_self(),drone->currentBattery);

	/* go back to the Mother Ship*/
	for(int i = 0 ; i < clients[size-1]->distance; ++i) {
		pthread_mutex_lock(&mutexLanes[trafficLane][1]);
		move2(drone,weight);
		usleep(100000);
		pthread_mutex_unlock(&mutexLanes[trafficLane][1]);
	}
	drone->state = Available;
	printf("Drone %d arrived at MotherShip  Battery : %d\n",pthread_self(),drone->currentBattery);

	/* update isDelivering*/
	for(int i = 0 ; i < size; ++i)
		isDelivering[clients[i]->id] = 0;

}


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

int computeTotalWeight(Client* clients[] ,int size) {
	int weight = 0;
	for( int i = 0; i < size ; ++i) {
		weight += clients[i]->command->weight;
	}
	return weight;
}

void move2(Drone* drone , int weight) {
	pthread_mutex_lock(&mutexWind);
	drone->currentBattery -= wind;
	pthread_mutex_unlock(&mutexWind);
	drone->currentBattery -= weight + MOVE_BATTERY_COST;
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
			Client** toDeliver = clientToDeliver2;
			int size = clientToDeliverSize;
			sem_post(&semSynch);
			//TODO : deliver With multiple clients
			deliver2(drone,toDeliver,size);
			//deliver(drone, toDeliver);
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

