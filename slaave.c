#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, const char *argv[])
{
	char command[];
	command = strcat("/bin/", argv[1]);
	execl(command ,argv[1],NULL );
	return 0;
}
