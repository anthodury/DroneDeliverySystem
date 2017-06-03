#ifndef DRONEDELIVERYSYSTEM_MOTHERSHIP_HPP
#define DRONEDELIVERYSYSTEM_MOTHERSHIP_HPP

#include <semaphore.h>
#include "Drone.h"
#define CHARGER 1
#define DRONES_NUMBER 4
#define CLIENT_NUMBER 200

//TODO: SLOTS

extern sem_t semRecharge;
extern Client* clients[];
extern Client* clientToDeliver;

extern Drone* drones[DRONES_NUMBER];
extern sem_t semDrones[DRONES_NUMBER];
extern sem_t semSynch;

extern int message;




void initMotherShip ();
void recharge(Drone* drone);
void * manageCommand(void *data);
int compareClients(const void * elem1, const void * elem2 );

#endif //DRONEDELIVERYSYSTEM_MOTHERSHIP_HPP
