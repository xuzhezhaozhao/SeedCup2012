#include <stdlib.h>
#include <stdio.h>


void main()
{
	int *p = NULL;

	p = (int *)malloc(sizeof(int));

	free(p);

	/*

	p = NULL;

	*/

	return;
}