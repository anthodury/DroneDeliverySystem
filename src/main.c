#include <stdio.h>
#include <pthread.h>
#include <MotherShip.h>

int main() {
	initMotherShip();
	pthread_exit(NULL);
	return 0;
}

