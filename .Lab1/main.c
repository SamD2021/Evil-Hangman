#include <stdio.h>
#include <stdlib.h>

#define ROWS 20
#define COLOMNS 30

int main (int argc, char* argv[])
{
	int i, j;
	int* TDarr[ROWS];
	for(i = 0; i < ROWS; i++)
	{
		TDarr[i] = (int*) malloc(COLOMNS * sizeof(int));
	}
	for(i = 0;i < ROWS; i++)
	{
		for(j=0;j<COLOMNS;j++)
		{
			TDarr[i][j] = j+i; 
		}
	}
	for(i = 0; i <20; i++)
	{

		for(j=0;j<30;j++)
		{
			printf("%4d", TDarr[i][j]);
				
		}
		printf("\n");
	}
	for(i = 0; i < ROWS; i++)
	{
		free(TDarr[i]);
	}
	return 0;
}