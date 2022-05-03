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
	puts(" ALARM  ");

	}

int main(){
	signal(SIGUSR1, manejador);
	pid_t son;
		
	son = fork() ;
	
	if(son>0){//Padre
		
		puts("Breakfast Time!");
		sleep(2);
		kill(son, SIGUSR1);
		
		pause();
		puts("Die...");
		kill(son, SIGKILL);
		
		
	}else{
		pause();
		
		puts("		Father woke me up ... 5 more secs please");
		sleep(3);
		puts("		Father wake up");
		kill(getppid(), SIGUSR1);
		
		pause();
		
	
	
	}
	
		return 0;
	
}


