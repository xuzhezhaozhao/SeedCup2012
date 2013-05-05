#include <stdlib.h>
#include <stdio.h>


void main()
{
	int *p[3] = {0};
	int i = 0;


	for (i = 0; i <= 1; i++)
	{
		p[i] = (int *)malloc(sizeof(int));
	}

	for (i = 0; i < 1; i++)
	{
		free(p[i]);
		p[i+1] = NULL;
	}
	

	return;
}