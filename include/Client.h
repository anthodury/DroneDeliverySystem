#ifndef DRONEDELIVERYSYSTEM_CUSTOMER_HPP
#define DRONEDELIVERYSYSTEM_CUSTOMER_HPP

#include <Package.h>
#include <pthread.h>

#define MAX_DISTANCE 50

typedef struct  {
	int distance;
	int trafficLane;
	Package* command;
} Client ;

Client createClient();
int isPresent(Client *client);
int hasTarget(Client *client);
void freeClient(Client * client);

#endif //DRONEDELIVERYSYSTEM_CUSTOMER_HPP
