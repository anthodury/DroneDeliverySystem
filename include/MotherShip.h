#ifndef DRONEDELIVERYSYSTEM_MOTHERSHIP_HPP
#define DRONEDELIVERYSYSTEM_MOTHERSHIP_HPP

#include <semaphore.h>
#include <Drone.h>
#define CHARGER 4
#define EXIT_NBR 1
#define DRONES_NUMBER 4
#define CLIENT_NUMBER 20

typedef enum {DELIVER,RECHARGE,FINISHED} Message;



extern sem_t semRecharge;
extern Client* clients[];
extern int isDelivered[CLIENT_NUMBER];
extern int isDelivering[CLIENT_NUMBER];

extern Client** clientToDeliver;
extern int clientToDeliverSize;

extern Drone* drones[DRONES_NUMBER];
extern sem_t semDrones[DRONES_NUMBER];
extern sem_t semSynch ;

extern sem_t semExit ;

extern Message message;


/*------------------------------------------------------------------------*//**
 *
 * @brief      initialize several mutex and semaphore, clients and drones,
 *             threads and others ...
 */
void initMotherShip ();

/*------------------------------------------------------------------------*//**
 * @brief      Recharges the battery of a given drone.
 *
 * @param[in]  drone The drone
 */
void recharge(Drone* drone);

/*------------------------------------------------------------------------*//**
 * @brief      The function of the MotherShip's thread.
 *
 * @param[in]  data Not used
 */
void * manageCommand(void *data);

/*------------------------------------------------------------------------*//**
 * @brief      Checks if all the clients are delivered.
 *
 * @return     returns if all the clients are delivered.
 */
int areAllDelivered();

#endif //DRONEDELIVERYSYSTEM_MOTHERSHIP_HPP
