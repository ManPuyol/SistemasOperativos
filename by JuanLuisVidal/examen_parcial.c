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
int input =0;
unsigned long long factorialNum =0;

//Este flag aumentara cuando terminen primo y fibonacci y cuando sea 2 volvera a activar el master
int masterFlag =0;
pthread_t  master, escribe, primo, fibonacci;

void manejador(int sig){

	}

unsigned long long factorial(int n){
	
		int i=1;
		unsigned long long fact =1;
	
		while(i<=n){
			fact=fact*i;
			i++;
		} 
		return fact;
}

void *getInputs(){
			
			while(input != -1){
				masterFlag =0;
				printf("\nSoy %u. Dame Numero:  ", (unsigned int)master);
				scanf("%d", &input);
				pthread_kill(escribe, SIGUSR1);
				
				pause();
				
				while (masterFlag< 2){sleep(1);}
				
				
			}
			
			pthread_kill(escribe, SIGKILL);
			pthread_kill(primo, SIGKILL);
			pthread_kill(fibonacci, SIGKILL);
			
			
			return 0;
	}
	
void *calcFactorial(){
	
			while(input != -1){
				pause();
				factorialNum = factorial(input);
				printf("Soy %u. El factorial de  %d es: %llu \n",(unsigned int)escribe , input, factorialNum);
				pthread_kill(primo, SIGUSR1);
				pthread_kill(fibonacci, SIGUSR1);
				pthread_kill(master, SIGUSR1);
				
			}
			
			return 0;
	}
	
	void *isPrimo(){
			
			while(input != -1){
				pause();
				
				int i;
				int flag=1;// 1 si es primo, 0 si no lo es
				
				for (i=2; i<factorialNum-1; i++){
					if (factorialNum-1%i == 0)
					{
						flag=0;
						//break;
					}
				}
				if (flag==1)
					printf("\nSoy %u. El numero %llu es primo", (unsigned int)primo,factorialNum-1);
				else 
					printf("\nSoy %u. El numero %llu no es primo", (unsigned int)primo, factorialNum-1);
					
				masterFlag ++;
				
			}
			

			return 0;
	}
	
	void *isInFibonacci(){
			
			while(input != -1){
				pause();
				
				unsigned long int i, t1 = 0, t2 = 1, siguiente;
				for (i = 1; i <= factorialNum-1; ++i) {
					
					
					if (factorialNum-1 == t1){
						printf("\nSoy %u. El numero %llu pertenece a fibonacci  ", (unsigned int)fibonacci ,factorialNum-1);
						break;
				
						}
					else if ( t1 > factorialNum-1){
						
						printf("\nSoy %u. El numero %llu no pertenece a fibonacci  ", (unsigned int)fibonacci ,factorialNum-1);
					break;
					
						}
						
					siguiente = t1 + t2;
					t1 = t2;
					t2 = siguiente;
				}
				masterFlag ++;

			}	
			
			return 0;
	}

int main(){
		signal(SIGUSR1, manejador);
		
		pthread_create(&escribe, NULL, &calcFactorial, NULL);
		pthread_create(&primo, NULL, &isPrimo, NULL);
		pthread_create(&fibonacci, NULL, &isInFibonacci, NULL);
		pthread_create(&master, NULL, &getInputs, NULL);

		pthread_join(escribe,NULL);	
		pthread_join(primo,NULL);	
		pthread_join(fibonacci,NULL);	
		pthread_join(master,NULL);			
		
		return 0;
	
}

