#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void *changeWeather(void *data)
{
    while(1){
        // Change weather
        // Notify drone and others ...
        printf("Weather changed\n");
        unsigned int timeWaiting=3+rand()%30;
        sleep(timeWaiting);
    }
}

int main() {
	printf("Hello, World!\n");

    pthread_t threadWeather;
	if (pthread_create(&threadWeather, 0, changeWeather,NULL)){
		printf("error creating thread weather");
	}
    //pthread_kill(threadWeather, SIGKILL);// Kill thread weather
    pthread_exit(NULL);
    
	return 0;
}