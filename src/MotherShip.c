#include <MotherShip.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <Weather.h>
#include <TrafficLanes.h>
#include <Drone.h>

sem_t semRecharge;
Client* clients[CLIENT_NUMBER];
int isDelivered[CLIENT_NUMBER];
int isDelivering[CLIENT_NUMBER];

Client** clientToDeliver;
int clientToDeliverSize = 0;


Drone* drones[DRONES_NUMBER];
sem_t semDrones[DRONES_NUMBER];
sem_t semSynch ;

sem_t semExit ;

// message for the current drone
Message message;




void recharge(Drone* drone) {
	int available ;
	sem_getvalue(&semRecharge,&available);
	if(available <=0) {
		printf("Drone %d WAITING for free charger\n", drone->id);
	}
	sem_wait(&semRecharge);
	printf("Drone %d RECHARGING : Battery : %d\n",drone->id,drone->currentBattery);
	for(int i = drone->currentBattery ; i < drone->maxBattery ; ++ i ) {
		usleep(10000);
		drone->currentBattery ++ ;
	}
	sem_post(&semRecharge);
	printf("Drone %d FINISHED RECHARGING\n", drone->id);
	drone->state=Available;
}

Client ** selectNeighborsClients(Drone *drone, Client *clientToDeliver, Client **selection, int* selectionSize){
    *selectionSize=1;
    Client **toTest=(Client**)malloc((*selectionSize+1) * sizeof(Client *));
    toTest[0]=clientToDeliver;

    for(int i=0;i<CLIENT_NUMBER;++i){
        if(!isDelivered[i] && !isDelivering[i] && clients[i]->trafficLane==clientToDeliver->trafficLane && clients[i]!=clientToDeliver) {
            toTest[*selectionSize]=clients[i];
            if (canDeliver2(drone, toTest, *selectionSize+1)) {
	            (*selectionSize)++;
                toTest=(Client**)realloc(toTest,sizeof(Client*)*(*selectionSize+1));// Increase toTest size
                //printf("Found new client to deliver on the same traject\n");
            }
        }
    }
    selection = malloc(*selectionSize * sizeof(Client *)) ;

	for(int i=0;i<*selectionSize;++i){
        selection[i]=toTest[i];
    }


	// maybe swap above loop by memcpy if it works
	//memcpy(selection,toTest,sizeof(Client*)*selectionSize);
    free(toTest);// Release memory space allocated to toTest
	return selection;
}

void * manageCommand(void *data) {
	printf("MotherShip thr : %lu\n", pthread_self());
	do {
		for(int i = 0; i < CLIENT_NUMBER; ++i) {
			if(!isDelivered[clients[i]->id] && !isDelivering[clients[i]->id]) {
				int found = 0;
				do {
					/* Find a drone who can deliver the client*/
					for(int k = 0; k < DRONES_NUMBER; ++k) {
						if(drones[k]->state == Available) {
							if(canDeliver(drones[k], clients[i])) {
								clientToDeliver = selectNeighborsClients(drones[k],clients[i],clientToDeliver,&clientToDeliverSize);
								printf("Drone %d will travel with %d client(s) to deliver\n",k,clientToDeliverSize);
								for(int j = 0 ; j < clientToDeliverSize;++j)
									isDelivering[clientToDeliver[j]->id] = 1;
								drones[k]->state = Moving;
								message = DELIVER;
								sem_post(&semDrones[k]); // m1 unlock
								sem_wait(&semSynch); // m2 lock
								found = 1;
								break;
							}
							else {
								message = RECHARGE;
								drones[k]->state = Recharging;
								sem_post(&semDrones[k]);
							}
						}
					}
				} while(!found);
			}
		}
	} while(!areAllDelivered()); // check if there is still client to deliver ( who weren't present when drone delivered)
	printf("FINISHED ALL COMMANDS\n");

	message = FINISHED;
	for(int i = 0; i < DRONES_NUMBER ; ++ i) {
		sem_post(&semDrones[i]);
	}
	return NULL;
}

int areAllDelivered(){
    for(int i=0;i<CLIENT_NUMBER;++i){
        if(!isDelivered[i])
	        return 0;
    }
    return 1;
}
/**
 * inits clients, drones, and mutex
 */
 void initMotherShip() {
	initLanesMutex();
	pthread_t threadDrone[DRONES_NUMBER];
	pthread_t threadWeather = initWeather();

	/* init drones struct and drone threads*/
	for(int i = 0 ; i < DRONES_NUMBER ; ++i) {
		sem_init(&semDrones[i],0,0);
		drones[i] = (Drone*) malloc(sizeof(Drone));
		*drones[i] = createDrone(i);
		pthread_create(&threadDrone[i],NULL,run,(void*)i);
	}
	/* init client struct*/
	for(int i = 0 ; i < CLIENT_NUMBER; ++i) {
		clients[i] = (Client*) malloc(sizeof(Client));
		*clients[i] = createClient();
		clients[i]->id = i;
	}

	pthread_t motherShipTh ;
	sem_init(&semSynch,0,0);
	sem_init(&semRecharge,0,CHARGER);
	sem_init(&semExit,0,EXIT_NBR);

	//Sorting clients by higher priority
	qsort(clients, CLIENT_NUMBER, sizeof(Client*), compareClientsByPriority);
	pthread_create(&motherShipTh,NULL,manageCommand,NULL);

	pthread_join(motherShipTh,NULL);
	for(int i = 0 ; i < DRONES_NUMBER; ++i) {
		pthread_join(threadDrone[i], NULL);
		free(drones[i]);
	}

	//if(pthread_cancel(threadWeather)) printf("Problem to stop Weather thread");
	pthread_join(threadWeather,NULL);

	for(int i = 0 ; i < CLIENT_NUMBER; ++i) {
		freeClient(clients[i]);
		free(clients[i]);
	}

}

