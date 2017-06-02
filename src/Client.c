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
	/**
	 * TO DO
	 */
	return 1;
}
int hasTarget(Client *client) {
	/**
	 * TO DO
	 */
	return 1;
}

void freeClient(Client * client) {
	free(client->command);
}

