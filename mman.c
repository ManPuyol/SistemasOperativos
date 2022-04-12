#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <sys/mman.h>

int main(int argc, const char *argv[])
{
	
	int *variable_compartida;
	
	variable_compartida = mmap(NULL, sizeof *variable_compartida, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	
	*variable_compartida =0;
	
	if(fork() >0){//Padre
		printf("Father here! Var is : %d \n", *variable_compartida);
		wait(NULL);
		printf("Father here! Var is now : %d \n", *variable_compartida);
	}else{
		printf("Son here! Var is : %d \nNew val :  ", *variable_compartida);
		scanf("%d", *&variable_compartida);
		exit(0);
	}
	
	munmap(variable_compartida, sizeof(variable_compartida));
	
	
}
