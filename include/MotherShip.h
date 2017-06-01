#ifndef DRONEDELIVERYSYSTEM_MOTHERSHIP_HPP
#define DRONEDELIVERYSYSTEM_MOTHERSHIP_HPP

#include <semaphore.h>
#include "Drone.h"
#define CHARGER 2
#define DRONES_NUMBER 50
#define CLIENT_NUMBER 200

// TODO : Slots, battery recharge, list of clients, list of drones , traffic lanes

extern sem_t semRecharge;
extern Client* clients [];
extern Client* clientToDeliver;

extern Drone* drones[DRONES_NUMBER];
extern pthread_mutex_t mutexDrones [DRONES_NUMBER];
extern pthread_mutex_t mutexClient;



void initMotherShip ();
void recharge(Drone* drone);
void * manageCommand(void *data);

#endif //DRONEDELIVERYSYSTEM_MOTHERSHIP_HPP
