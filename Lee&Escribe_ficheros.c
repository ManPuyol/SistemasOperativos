#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#define SIZE  256

pthread_t  lee, escribe, leeFichero;
char inputText[SIZE];

void manejador(int sig){

	}
	
	
void *leeTeclado(){
	
		printf("\nSoy %u. Dame texto:  ", (unsigned int)lee);
		fgets( inputText, SIZE, stdin);
		pthread_kill(escribe, SIGUSR1);
			
			return 0;
	}
	
void *escribeFromTeclado(){
		
		pause();
		printf("\nSoy %u. Vamos a guardar \n\n %s ", (unsigned int)escribe, inputText);
		
		int fd;
	
		fd = open("text.txt", O_RDWR);
		write(fd, inputText, SIZE);
		close(fd);
		
		
		pthread_kill(leeFichero, SIGUSR1);
			
			return 0;
	}
	
void *readFichero(){
		
		pause();
		
		int fd;
		char textFromFile[SIZE];
	
		fd = open("text.txt", O_RDWR);
		read(fd, textFromFile, SIZE);
		
		printf("\nSoy %u. Se guardo %s   \nEn el fichero text.txt", (unsigned int)leeFichero, textFromFile);
			close(fd);
			return 0;
	}

int main(){
		signal(SIGUSR1, manejador);
		
		pthread_create(&lee, NULL, &leeTeclado, NULL);
		pthread_create(&escribe, NULL, &escribeFromTeclado, NULL);
		pthread_create(&leeFichero, NULL, &readFichero, NULL);

		pthread_join(lee,NULL);	
		pthread_join(escribe,NULL);	
		pthread_join(leeFichero,NULL);			
		
		return 0;
	
}
