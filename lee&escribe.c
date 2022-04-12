#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <sys/mman.h>
#include <sys/types.h>


int main(int argc, const char *argv[])
{
	pid_t lee, escribe;
	
	int *variable_compartida;
	
	variable_compartida = mmap(NULL, sizeof *variable_compartida, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	
	*variable_compartida =-1010000;
	
	lee = fork() ;
	
	if(lee>0){//Padre
		escribe = fork();
		
		if(escribe == 0){//escribe
			while(*variable_compartida == -1010000){}
			
			printf("\nSe introdujo: %d \n", *variable_compartida);
			
		}
		
		wait(NULL);
		
		
	}else{//lee
		
		printf("Dame Numero:  ");
		scanf("%d", *&variable_compartida);
		exit(0);
	}
	
	munmap(variable_compartida, sizeof(variable_compartida));
	
	
}
