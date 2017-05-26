#ifndef DRONEDELIVERYSYSTEM_DRONE_HPP
#define DRONEDELIVERYSYSTEM_DRONE_HPP

#include "Package.h"
#include "Client.h"

/* Available : at mother ship , Waiting : Drone arrived client's garden and waiting for him*/
typedef enum {Available,Moving,Waiting} State;

typedef struct {
	int maxBattery;
	int currentBattery;
	State state;
} Drone;

Drone createDrone();
int canDeliver(Drone* drone, Client* client);
void deliver(Drone* drone, Client* client);
#endif //DRONEDELIVERYSYSTEM_DRONE_HPP
