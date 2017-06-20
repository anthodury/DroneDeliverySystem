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

/*------------------------------------------------------------------------*//**
 * @brief      Randomly creates a client.
 *
 * @return     returns a random client.
 */
Client createClient();

/*------------------------------------------------------------------------*//**
 * @brief      check with probability, if a client is here.
 *
 * @return     returns if the client is here.
 */
int isPresent();

/*------------------------------------------------------------------------*//**
 * @brief      check with probability, if a client's target is here.
 *
 * @return     returns if the client's target is here.
 */
int hasTarget();

/*------------------------------------------------------------------------*//**
 * @brief      free the memory allocated  to a client.
 *
 * @param[in]  client The client to deliver.
 */
void freeClient(Client * client);

/*------------------------------------------------------------------------*//**
 * @brief      compares clients by priority, used for standard qsort.
 *
 * @param[in]  elem1 First client to compare.
 * @param[in]  elem1 Second client to compare.
 *
 * @return  a negative integer, zero, or a positive integer as the second
 *          argument is less than, equal to, or greater than the first.
 */
int compareClientsByPriority(const void* elem1, const void* elem2);

/*------------------------------------------------------------------------*//**
 * @brief      compares clients by distance, used for standard qsort.
 *
 * @param[in]  elem1 First client to compare.
 * @param[in]  elem1 Second client to compare.
 *
 * @return  a negative integer, zero, or a positive integer as the first
 *          argument is less than, equal to, or greater than the second.
 */
int compareClientsByDistance(const void* elem1, const void* elem2) ;


#endif //DRONEDELIVERYSYSTEM_CUSTOMER_HPP
