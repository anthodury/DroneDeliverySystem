#include "Package.h"

#ifndef DRONEDELIVERYSYSTEM_CUSTOMER_HPP
#define DRONEDELIVERYSYSTEM_CUSTOMER_HPP

typedef struct  {
	int distance;
	int trafficLane;
	Package* command;
} Client ;

Client createClient();
int isPresent(Client *client);
int hasTarget(Client *client);


#endif //DRONEDELIVERYSYSTEM_CUSTOMER_HPP
