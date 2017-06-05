#ifndef DRONEDELIVERYSYSTEM_DRONE_HPP
#define DRONEDELIVERYSYSTEM_DRONE_HPP

#include <Package.h>
#include <Client.h>
#define MAX_BATTERY 2000
#define MOVE_BATTERY_COST 2

/* Available : at mother ship , Waiting : Drone arrived client's garden and waiting for him*/
typedef enum {Available,Moving,Waiting} State;

typedef struct {
	int maxBattery;
	int currentBattery;
	State state;
} Drone;

Drone createDrone();

/*
 * returns if the Drone has enough battery to deliver the Client client
 */
int canDeliver(Drone* drone, Client* client);

/*
 * Delivers the client
 */
void deliver(Drone* drone, Client* client);

/*
 * moves
 */
void move(Drone* drone, Client* client);

/*
 * thread handler
 */
void * run (void * data) ;
pthread_t initDrone (int index) ;

int targetAndClientPresent(Client* client);


#endif //DRONEDELIVERYSYSTEM_DRONE_HPP
