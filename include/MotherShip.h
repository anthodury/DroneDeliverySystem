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
extern int isDelivered[CLIENT_NUMBER];
extern int isDelivering[CLIENT_NUMBER];

extern Client* clientToDeliver;
extern Client** clientToDeliver2;
extern int clientToDeliverSize;

extern Drone* drones[DRONES_NUMBER];
extern sem_t semDrones[DRONES_NUMBER];
extern sem_t semSynch;

extern int message;




void initMotherShip ();
void recharge(Drone* drone);
void * manageCommand(void *data);
int areAllDelivered();

#endif //DRONEDELIVERYSYSTEM_MOTHERSHIP_HPP
