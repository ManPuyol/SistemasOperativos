#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

int main(int argc, const char *argv[])
{

	int tuberia1[2];
	int tuberiaResult[2];
	
	pipe(tuberiaResult);
	pipe(tuberia1);
	
		
		if(fork()>0){//padre
			close(tuberia1[0]);
			close(tuberiaResult[1]);

			int input1, input2, result=4;

			puts("Insert two numbers: ");
			scanf ("%d",&input1);
			scanf ("%d",&input2);
	

			write(tuberia1[1], &input1, sizeof(input1) );
			write(tuberia1[1], &input2, sizeof(input2) );
			
			//sleep(2);
			read(tuberiaResult[0], &result, sizeof(result) );
			printf("\nSe recibio \n-- %d --\nDe el hijo", result);
			
			
		}else{//child
			close(tuberia1[1]);
			close(tuberiaResult[0]);
			
			int input1, input2, res;
			

			read(tuberia1[0], &input1, sizeof(input1) );
			read(tuberia1[0], &input2, sizeof(input2) );
			
			printf("\n 1 -- %d \n 2 -- %d ", input1, input2);
			
			res = input1+input2;
			
			write(tuberiaResult[1], &res, sizeof(res) );
			printf("\nSoy el hijo y sume -- %d \n", res);
			exit(0);
			
		}
		
	return 0;
}
