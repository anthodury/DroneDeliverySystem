#include <stdio.h>
#include <pthread.h>
#include <MotherShip.h>

void main() {
	initMotherShip();
	pthread_exit(NULL);
}

