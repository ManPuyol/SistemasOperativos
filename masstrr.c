#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

int main(int argc, const char *argv[])
{
	
		
		char input[5];
		puts("Enter Shell command: \n	ls \n	pwd \n	ps \n	who \n	exit \n");
		scanf ("%s",input);
   
		while(strcmp(input, "exit") != 0){
			
			
			if(fork()==0){//Child
				execl("./slaave","slaave", input,NULL );
			}else{
				wait(NULL);
				scanf ("%s",input);
			}
		}

			
	
	
	
	
	return 0;
}
