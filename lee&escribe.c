#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h>


sem_t *semaforo;

int main(int argc, const char *argv[])
{
	sem_unlink("/mis");
	pid_t lee, escribe;
	
	int *variable_compartida;
	
	variable_compartida = mmap(NULL, sizeof *variable_compartida, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	semaforo = sem_open("/mis", O_CREAT, S_IRUSR | S_IWUSR,1);
	
	*variable_compartida =-1010000;
	
	lee = fork() ;
	
	if(lee>0){//Padre
		escribe = fork();
		
		if(escribe == 0){//escribe
			sleep(1);
			sem_wait(semaforo);
			printf("\nSe introdujo: %d \n", *variable_compartida);
			sem_post(semaforo);
			exit(0);
		}//escribe--END
		
		while(wait(NULL)>0);
		sem_unlink("/mis");
		
		
	}else{//lee
		
		sem_wait(semaforo);
		printf("Dame Numero:  ");
		scanf("%d", *&variable_compartida);
		sem_post(semaforo);
		
		exit(0);
	}
	
	munmap(variable_compartida, sizeof(variable_compartida));
	
	
}
