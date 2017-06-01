#include <MotherShip.h>
#include <Drone.h>
#include <unistd.h>
#include <stdio.h>
#include <Client.h>
#include <Package.h>
#include <malloc.h>

sem_t semRecharge;
Client* clients[CLIENT_NUMBER];
Client* clientToDeliver;

Drone* drones[DRONES_NUMBER];
pthread_cond_t condDrones [DRONES_NUMBER];
pthread_mutex_t mutexDrones [DRONES_NUMBER];

void recharge(Drone* drone) {
	int available ;
	sem_getvalue(&semRecharge,&available);
	printf("Recharge Available : %d\n",available);
	sem_wait(&semRecharge);
	for(int i = drone->currentBattery ; i < drone->maxBattery ; ++ i ) {
		usleep(100000);
		drone->currentBattery ++ ;
        printf("Drone %d Recharging %d\n", (int) pthread_self(), drone->currentBattery);
	}
	sem_post(&semRecharge);
}

void runMotherShipThr() {

	while(1) {

	}
}

void * manageCommand(void *data) {
	int clientsSize = CLIENT_NUMBER;
	for(int i = 0 ; i < CLIENT_NUMBER;++i) {
		Client* toDeliver = clients[i];
		/* Find a drone who can deliver the client*/
		// TODO : While loop instead, recharge when cant deliver and available
		for(int k = 0; k < DRONES_NUMBER; ++k) {
			if(drones[k]->state == Available && canDeliver(drones[k], toDeliver)) {
				// unlock the mutex so that the drone's thread can run
				pthread_mutex_unlock(&mutexDrones[i]);
				clientToDeliver = toDeliver;

				break;
			}
		}
	}

	return NULL;
}

/**
 * inits clients, drones, and mutex
 */
 void initMotherShip() {
	for(int i = 0 ; i < DRONES_NUMBER ; ++i) {
	//	pthread_cond_init(&condDrones[i],NULL);
		pthread_mutex_init(&mutexDrones[i],NULL);

		drones[i] = (Drone*) malloc(sizeof(Drone));
		*drones[i] = createDrone();
		// blocks the drone thread, waiting to deliver
		pthread_mutex_lock(&mutexDrones[i]);
		initDrone(i);

	}
	for(int i = 0 ; i < CLIENT_NUMBER; ++i) {
		clients[i] = (Client*) malloc(sizeof(Drone));
		*clients[i] = createClient();
	}
	// TODO :sort Clients by priority
	pthread_t motherShipTh ;
	pthread_create(&motherShipTh,NULL,manageCommand,NULL);
}