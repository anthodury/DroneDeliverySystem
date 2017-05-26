#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "Weather.h"

int main() {
	printf("Hello, World!\n");

    pthread_t threadWeather;
    threadWeather=initWeather();

    //pthread_kill(threadWeather, SIGKILL);// Kill thread weather
    pthread_exit(NULL);

	return 0;
}