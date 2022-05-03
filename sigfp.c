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

int a;

void manejador(int sig){
	puts(" ...  dumas");
	a = 0;
	//pause();
	}

int main(){
	
	char c;
		signal(SIGFPE, manejador);
		//while(1){
			puts("2 / 0 = ");
			//raise(SIGUSR1);
			scanf("%c",&c );
			a = 2/0;
			sleep(1);
		//}
		printf("%d", a);
		return 0;
	
}

