#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h>
#define LIMIT 10000000

int *variable_compartida;
sem_t *semaforo;

int main(int argc, const char *argv[])
{
	pid_t suma , resta;
	
	
	int i;
	
	variable_compartida = mmap(NULL, sizeof *variable_compartida, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	semaforo = sem_open("/misemaforo", O_CREAT, S_IRUSR,1);
	
	*variable_compartida=0;
	
	suma = fork() ;
	
	
	
	if(suma>0){//Padre
		resta = fork();
		
		if(resta == 0){//resta
			for(i=0;i < LIMIT; i++){
				
			//asm volatile("cli":  :  : "memory");
			sem_wait(semaforo);
			*variable_compartida = *variable_compartida -1;
			sem_post(semaforo);
			//asm volatile("cli":  :  : "memory");
			
			if(i%(LIMIT/100)== 0){
				printf("Restando... %d\n", *variable_compartida );
				}
			}
			exit(0);
		}
		
		while (wait(NULL) > 0);
		printf("Final: %d", *variable_compartida );
		sem_unlink("/misemaforo");
		
	}else{//suma
		
		for(i=0; i < LIMIT; i++){
			//asm volatile("cli":  :  : "memory");
			sem_wait(semaforo);
			*variable_compartida = *variable_compartida +1;
			sem_post(semaforo);
			//asm volatile("cli":  :  : "memory");
			if(i%(LIMIT/100) == 0){
				printf("Sumando...  %d\n", *variable_compartida );
				}
			}
		exit(0);
	}
	
	munmap(variable_compartida, sizeof(variable_compartida));
	
	
}

