#include <Client.h>
#include <Drone.h>
#include <Weather.h>
#include <TrafficLanes.h>
#include <MotherShip.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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


void  deliver(Drone* drone,Client * toDeliver [] , int size) {
	int distance = 0;
	int weight = computeTotalWeight(toDeliver,size);
	int trafficLane = toDeliver[0]->trafficLane;

	//sort clients by  increasing distance
	qsort(toDeliver,size,sizeof(Client*),compareClientsByDistance);
	//printf(" sort : %d %d",clients[0]->distance,clients[1]->distance);

	/* go deliver all clients*/
	for(int i = 0 ; i < size; ++i) {
		for(distance;distance < toDeliver[i]->distance ; ++distance) {
			pthread_mutex_lock(&mutexLanes[trafficLane][0]);
			move(drone,weight);
			usleep(MOVE_DURATION);
			pthread_mutex_unlock(&mutexLanes[trafficLane][0]);
		}
		if(targetAndClientPresent(toDeliver[i])) {
			printf("Drone %d delivered client %d\n",pthread_self(),toDeliver[i]->id);
			isDelivered[toDeliver[i]->id] = 1;
			weight -= toDeliver[i]->command->weight;
		}
	}
	printf("Drone %d delivered last Client, Battery : %d \n",pthread_self(),drone->currentBattery);

	/* go back to the Mother Ship*/
	for(int i = 0 ; i < toDeliver[size-1]->distance; ++i) {
		pthread_mutex_lock(&mutexLanes[trafficLane][1]);
		move(drone,weight);
		usleep(MOVE_DURATION);
		pthread_mutex_unlock(&mutexLanes[trafficLane][1]);
	}
	printf("Drone %d arrived at MotherShip  Battery : %d\n",pthread_self(),drone->currentBattery);

	/* update isDelivering*/
	for(int i = 0 ; i < size; ++i)
		isDelivering[toDeliver[i]->id] = 0;
	drone->state = Available;
	free(toDeliver);

}


int targetAndClientPresent(Client* client){
	int targetPresent=0;
	//Wait 10 secondes max before leave if target is not present
	for(int i=0;i<10;++i){
		if(hasTarget(client) ){
			targetPresent=1;
			//printf("OK, target is present\n");
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
				//printf("OK, client is present\n");
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

void move(Drone* drone , int weight) {
	pthread_mutex_lock(&mutexWind);
	drone->currentBattery -= wind;
	pthread_mutex_unlock(&mutexWind);
	drone->currentBattery -= weight + MOVE_BATTERY_COST;
}


void * run (void * data) {
	int id = (int) data;
	Drone* drone = drones[id];

	while(1) {
		/* wait for MotherShip to unlock */
		sem_wait(&semDrones[id]);
		if(message == FINISHED)
			break;
		if(message == DELIVER) {
			Client** toDeliver = clientToDeliver;
			int size = clientToDeliverSize;
			sem_post(&semSynch);
			deliver(drone,toDeliver,size);
		}
		else {
			recharge(drone);
		}
	}

}


