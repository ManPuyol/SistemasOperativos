
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

#define SIZE  256

int main(){
	
	
	char nombre[]="text.txt";
	char buffer[SIZE];
	
	int fd, nleido;
	
	fd = open(nombre, O_RDONLY);
	
	while((nleido = read(fd, buffer, SIZE))>0)
	{
		printf("\nHe leido %d bytes\n", nleido);
		buffer[nleido]='\0';
		printf("%s", buffer);
	}
	
	close(fd);
	return 0;
	
	
	}


