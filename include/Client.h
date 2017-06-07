#ifndef DRONEDELIVERYSYSTEM_CUSTOMER_HPP
#define DRONEDELIVERYSYSTEM_CUSTOMER_HPP

#include <Package.h>
#include <pthread.h>

#define MAX_DISTANCE 50
#define PERCENTAGE_PRESENCE_CLIENT 40
#define PERCENTAGE_PRESENCE_TARGET 50

typedef struct  {
	int distance;
	int trafficLane;
	Package* command;
	int id;
} Client ;

Client createClient();
int isPresent(Client *client);
int hasTarget(Client *client);
void freeClient(Client * client);

int compareClientsByPriority(const void* elem1, const void* elem2);
int compareClientsByDistance(const void* elem1, const void* elem2) ;


#endif //DRONEDELIVERYSYSTEM_CUSTOMER_HPP
