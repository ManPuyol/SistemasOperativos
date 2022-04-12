#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <sys/mman.h>


int factorial(int n){
	
		int i=1, fact =1;
	
		while(i<=n){
			fact=fact*i;
			i++;
		} 
		return fact;
}

int main(int argc, const char *argv[])
{
	
	int *variable_compartida;
	
	variable_compartida = mmap(NULL, sizeof *variable_compartida, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	
	*variable_compartida =-1010000;
	
	if(fork() >0){//Padre
		printf("Dame Numero:  ");
		scanf("%d", *&variable_compartida);
		wait(NULL);
		printf("Factorial es: %d \n", *variable_compartida);
		
	}else{//Hijo
		//jejejej... child does the waiting
		while(*variable_compartida == -1010000){}
		
		printf("Hijo Calculando...\n");
		
	
		*variable_compartida = factorial(*variable_compartida);
		exit(0);
	}
	
	munmap(variable_compartida, sizeof(variable_compartida));
	
	
}
