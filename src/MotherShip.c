#include <MotherShip.h>
#include <Drone.h>
#include <unistd.h>
#include <stdio.h>
#include <Client.h>
#include <Package.h>
#include <malloc.h>
#include <stdlib.h>

sem_t semRecharge;
Client* clients[CLIENT_NUMBER];
Client* clientToDeliver;

Drone* drones[DRONES_NUMBER];
//pthread_mutex_t semDrones [DRONES_NUMBER];
sem_t semDrones[DRONES_NUMBER];
sem_t semSynch ;
int message;


void recharge(Drone* drone) {
	int available ;
	sem_getvalue(&semRecharge,&available);
	if(available <=0) {
		printf("Drone %d WAITING for free charger\n", pthread_self());
	}
	sem_wait(&semRecharge);
	printf("Drone %d RECHARGING : Battery : %d\n",pthread_self(),drone->currentBattery);
	for(int i = drone->currentBattery ; i < drone->maxBattery ; ++ i ) {
		usleep(10000);
		drone->currentBattery ++ ;
	}
	sem_post(&semRecharge);
	printf("Drone %d FINISHED RECHARGING\n", pthread_self());
	drone->state=Available;
}

void runMotherShipThr() {

	while(1) {

	}
}

void * manageCommand(void *data) {
	printf("MotherShip thr : %d",pthread_self());
	for(int i = 0 ; i < CLIENT_NUMBER;++i) {
		Client* client = clients[i];
		clientToDeliver = clients[i];
		/* Find a drone who can deliver the client*/
		int found = 0;
		do {
			for(int k = 0; k < DRONES_NUMBER; ++k) {
				if(drones[k]->state == Available) {
					if(canDeliver(drones[k], clientToDeliver)) {
						// unlock the mutex so that the drone's thread can run
						drones[k]->state = Moving;

						message = 1;
						//pthread_mutex_unlock(&semDrones[k]);
						sem_post(&semDrones[k]);
						sem_wait(&semSynch);
						found = 1;
						break;
					}
					else {
						message = 0;
						drones[k]->state = Moving;
						//pthread_mutex_unlock(&semDrones[k]);
						sem_post(&semDrones[k]);

						//message to recharge
					}
				}
			}
		} while(!found);
	}
	return NULL;
}

/**
 * inits clients, drones, and mutex
 */
 void initMotherShip() {
	for(int i = 0 ; i < DRONES_NUMBER ; ++i) {

		//pthread_mutex_init(&semDrones[i],NULL);
		sem_init(&semDrones[i],0,0);
		drones[i] = (Drone*) malloc(sizeof(Drone));
		*drones[i] = createDrone();
		initDrone(i);
	}

	for(int i = 0 ; i < CLIENT_NUMBER; ++i) {
		clients[i] = (Client*) malloc(sizeof(Drone));
		*clients[i] = createClient();
	}

	pthread_t motherShipTh ;
	sem_init(&semSynch,0,0);
	sem_init(&semRecharge,0,CHARGER);

	//Sorting clients by higher priority
	qsort(clients,CLIENT_NUMBER,sizeof(clients[0]),compareClients);
	pthread_create(&motherShipTh,NULL,manageCommand,NULL);
}

int compareClients(const void * elem1, const void * elem2 ) {
	Client * cl1 = *((Client**) elem1), *cl2 = *((Client**) elem2);
	return cl2->command->priority - cl1->command->priority;
}