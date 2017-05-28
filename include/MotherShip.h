#ifndef DRONEDELIVERYSYSTEM_MOTHERSHIP_HPP
#define DRONEDELIVERYSYSTEM_MOTHERSHIP_HPP

#include <semaphore.h>
#include "Drone.h"
#define CHARGER 2

// TODO : Slots, battery recharge, list of clients, list of drones , traffic lanes

sem_t semRecharge;

void recharge(Drone* drone);
#endif //DRONEDELIVERYSYSTEM_MOTHERSHIP_HPP
