#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>

pthread_mutex_t lock;
pthread_t  hilo1, hilo2;
pid_t id_proc;


void *workHilo1(){

	while(1){
			
			sleep(5);
			puts("		Detengamos el hilo 2");
			pthread_mutex_lock(&lock);
			kill(id_proc, SIGURG);
			sleep(5);
			
			pthread_mutex_unlock(&lock);
	}

return 0;
}

void *workHilo2(){

	id_proc=syscall(__NR_gettid);
	printf("PID es %d", id_proc);
	
	while(1){
			printf("Hilo 2 trabajando...");
			sleep(2);
	}

return 0;
}

void manejador(int sig){
pthread_mutex_lock(&lock);
pthread_mutex_unlock(&lock);
	}

int main(){
	
	signal(SIGURG, manejador);
	
	pthread_create(&hilo1, NULL, &workHilo1, NULL);
	pthread_create(&hilo2, NULL, &workHilo2, NULL);
	pthread_join(hilo1,NULL);
	pthread_join(hilo2,NULL);
	

	
		return 0;
	
}

