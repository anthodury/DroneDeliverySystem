#ifndef DRONEDELIVERYSYSTEM_DRONE_HPP
#define DRONEDELIVERYSYSTEM_DRONE_HPP

#include <Package.h>
#include <Client.h>
#define MOVE_BATTERY_COST 2
#define MOVE_DURATION 100000
#define MAX_BATTERY 2*MAX_DISTANCE*(MAX_WEIGHT+MOVE_BATTERY_COST+MAX_WIND) + 1


/* Available : at mother ship , Waiting : Drone arrived client's garden and waiting for him*/
typedef enum {Available,Moving,Waiting,Recharging} State;

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
int canDeliver2(Drone* drone, Client *arrayClients[], int size);

/*
 * Delivers the client
 */
void  deliver(Drone* drone,Client * toDeliver[] , int size);


/*
 * moves
 */
void move(Drone* drone , int weight) ;



/*
 * thread handler
 */
void * run (void * data) ;

int targetAndClientPresent(Client* client);

int computeTotalWeight(Client* clients[] ,int size);

#endif //DRONEDELIVERYSYSTEM_DRONE_HPP
