#include <MotherShip.h>
#include <Drone.h>
#include <unistd.h>
#include <stdio.h>

void recharge(Drone* drone) {

	drone->currentBattery = 95;

	int available ;
	sem_getvalue(&semRecharge,&available);
	printf("Recharge Available : %d\n",available);
	sem_wait(&semRecharge);
	for(int i = drone->currentBattery ; i < drone->maxBattery ; ++ i ) {
		usleep(100000);
		drone->currentBattery ++ ;
		printf("Drone %li Recharging %d\n",__threadid(), drone->currentBattery);
	}
	sem_post(&semRecharge);
}
