#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <Package.h>
#include <Drone.h>
#include <Weather.h>
#include <TrafficLanes.h>
#include <MotherShip.h>

int main() {
	initLanesMutex();

	printf("Hello, World!\n");

    pthread_t threadWeather;
    threadWeather=initWeather();

    //pthread_kill(threadWeather, SIGKILL);// Kill thread weather

	Package packageTest = createPackage();
	Client client = createClient();
	printf("Package test : %d %d %d\n",packageTest.id,packageTest.priority,packageTest.weight);
	printf("Client test %d %d %d ", client.trafficLane, client.distance, client.command->weight);
	freeClient(&client);



	initMotherShip();

	pthread_exit(NULL);

	return 0;
}