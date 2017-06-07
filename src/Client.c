#include <Package.h>
#include <stdlib.h>
#include <Client.h>
#include <TrafficLanes.h>

Client createClient() {
	Package * package = (Package*) malloc(sizeof(Package));
	*package = createPackage();
	return (Client) {1+(rand()%MAX_DISTANCE),rand()%MAX_TRAFFIC_LANES,package};
}

int isPresent(Client *client) {
	return ((rand()%100) < PERCENTAGE_PRESENCE_CLIENT);
}
int hasTarget(Client *client) {
	return ((rand()%100) < PERCENTAGE_PRESENCE_TARGET);
}

void freeClient(Client * client) {
	free(client->command);
}

int compareClientsByPriority(const void* elem1, const void* elem2) {
	Client * cl1 = *((Client**) elem1), *cl2 = *((Client**) elem2);
	return cl2->command->priority - cl1->command->priority;
}

int compareClientsByDistance(const void* elem1, const void* elem2) {
	Client * cl1 = *((Client**) elem1), *cl2 = *((Client**) elem2);
	return cl1->distance - cl2->distance;
}