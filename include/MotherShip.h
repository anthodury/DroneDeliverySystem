#ifndef DRONEDELIVERYSYSTEM_MOTHERSHIP_HPP
#define DRONEDELIVERYSYSTEM_MOTHERSHIP_HPP

#include <semaphore.h>
#include <Drone.h>
#define CHARGER 4
#define EXIT_NBR 1
#define DRONES_NUMBER 4
#define CLIENT_NUMBER 20

typedef enum {DELIVER,RECHARGE,FINISHED} Message;


//TODO: SLOTS

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



void initMotherShip ();
void recharge(Drone* drone);
void * manageCommand(void *data);
int areAllDelivered();

#endif //DRONEDELIVERYSYSTEM_MOTHERSHIP_HPP
