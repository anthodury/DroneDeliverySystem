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


/*------------------------------------------------------------------------*//**
 * @brief      Compute if the drone has enough battery to deliver the client.
 *
 * @param[in]  drone  The drone
 * @param[in]  client The client to deliver
 *
 * @return     returns if the drone has enough battery to deliver the client.
 */
int canDeliver(Drone* drone, Client* client);

/*------------------------------------------------------------------------*//**
 * @brief      Compute if the drone has enough battery to deliver several
 *             clients.
 *
 * @param[in]  drone  The drone
 * @param[in]  arrayClients The clients to deliver
 * @param[in]  size The number of client to deliver
 *
 * @return     returns if the drone has enough battery to deliver the
 *             clients.
 */
int canDeliver2(Drone* drone, Client *arrayClients[], int size);

/*------------------------------------------------------------------------*//**
 * @brief      Manages the delivery of several clients by a drone
 *
 * @param[in]  drone  The drone
 * @param[in]  arrayClients The clients to deliver
 * @param[in]  size The number of client to deliver
 *
 */
void  deliver(Drone* drone,Client * toDeliver[] , int size);


/*------------------------------------------------------------------------*//**
 * @brief      Make the drone move one distance.
 *
 * @param[in]  drone  The drone
 * @param[in]  weight The total weight of the transported packages.
 *
 */
void move(Drone* drone , int weight) ;



/*
 * thread handler
 */
void * run (void * data) ;

int targetAndClientPresent(Client* client);

int computeTotalWeight(Client* clients[] ,int size);

#endif //DRONEDELIVERYSYSTEM_DRONE_HPP
