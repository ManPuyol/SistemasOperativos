#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
#define LIMIT 1000000


int  variable_compartida;
sem_t *semaforo;
pthread_mutex_t lock;

void *sumaF(){
	int i;

	for(i=0; i < LIMIT; i++){
			
			//sem_wait(semaforo);
			pthread_mutex_lock(&lock);
			variable_compartida = variable_compartida +1;
			pthread_mutex_unlock(&lock);
			//sem_post(semaforo);
			
			if(i%(LIMIT/100) == 0){
				//sem_wait(semaforo);
				pthread_mutex_lock(&lock);
				printf("Sumando...  %d\n", variable_compartida );
				pthread_mutex_unlock(&lock);
				//sem_post(semaforo);
				}
			}
			
			return 0;
	}


void *restaF(){
	int i;
	for(i=0;i < LIMIT; i++){
			
			//sem_wait(semaforo);
			pthread_mutex_lock(&lock);
			variable_compartida = variable_compartida -1;
			pthread_mutex_unlock(&lock);
			//sem_post(semaforo);
								
			if(i%(LIMIT/100)== 0){
				//sem_wait(semaforo);
				pthread_mutex_lock(&lock);
				printf("Restando... %d\n", variable_compartida );
				pthread_mutex_unlock(&lock);
				//sem_post(semaforo);
				}
			}
			
			return 0;
	}
	
	
int main(int argc, const char *argv[])
{
	//sem_unlink("/misemaforo");
	//semaforo = sem_open("/misemaforo", O_CREAT,  S_IRUSR | S_IWUSR,1);
	
	pthread_mutex_init(&lock,NULL);
	
	pthread_t suma , resta;
	pthread_create(&suma, NULL, &sumaF, NULL);
	pthread_create(&resta, NULL, &restaF, NULL);
	pthread_join(suma,NULL);
	pthread_join(resta,NULL);	
		
	printf("Final: %d", variable_compartida );
	
	pthread_mutex_destroy(&lock);
	
	//sem_close(semaforo);
	//sem_unlink("/misemaforo");
	
	return 0;
}


