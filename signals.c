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

void manejador(int sig){
	puts(" ...  ");
	//pause();
	}


int main(){
	
		signal(SIGINT, manejador);
		while(1){
			puts("Message");
			sleep(1);
		}
		
		return 0;
	
}


