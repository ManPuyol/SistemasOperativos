
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#define SIZE  256

int main(){
	
	char my_dir[SIZE];
	
	struct dirent *direntp;
	DIR *dirp;
	
	getcwd(my_dir, SIZE);
	
	dirp = opendir(my_dir);
	
	while((direntp = readdir(dirp))!= NULL)
	{
		printf("%s \t %d \n", direntp->d_name, direntp->d_reclen);
		}
	
	
	}

