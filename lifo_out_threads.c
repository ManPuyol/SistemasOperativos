#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
#define LIMIT 10
//Create flag to wait for user input
char c = '@';

pthread_mutex_t lock;

//Create flag to stop threads in order
int activeThread = 1;

void *work(){
	//Define ID for this thread when it starts
	int threadID = activeThread;
	
	//Print Thread startup
	printf("#%d - He nacido soy  %u \n", threadID, (unsigned int)pthread_self());
	
	//wait for user input and turn
	while(c =='@' || threadID != activeThread){}
	
	
	//Print Thread startup death
	printf("#%d  Me voy %u \n", threadID, (unsigned int)pthread_self());	
	
	//Change global flag announcing next turn. Using Mutex to avoid colisions
	pthread_mutex_lock(&lock);
	activeThread = activeThread -1;
	pthread_mutex_unlock(&lock);	

return 0;
}

	
int main(int argc, const char *argv[]){	
	
	pthread_mutex_init(&lock,NULL);
	
	//Defune Thread array with previously defined LIMIT
	pthread_t  hilos[LIMIT];
	int i;
	for(i=0; i < LIMIT; i++){
			pthread_create(&hilos[i], NULL, &work, NULL);
			activeThread = i+1;
			sleep(1);
		}
		
	//wait for user input
	scanf("%c",&c);
	
	//Wait for all Threads to finish
	for(i=LIMIT-1; i >=0; i--){
		pthread_join(hilos[i],NULL);
		}

	pthread_mutex_destroy(&lock);
	
	return 0;
}
