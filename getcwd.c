#include <stdio.h>
#include <unistd.h>
#define SIZE  256

int main(){
	
	char my_dir[SIZE];
	
	if(getcwd(my_dir, SIZE)==NULL) {
		return -1;
		
	}else{
		printf("%s", my_dir);
	}
	
	
	}

