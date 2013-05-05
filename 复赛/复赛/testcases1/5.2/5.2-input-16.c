
#include <stdlib.h>
#include <stdio.h>

void myFree(char * p)
{
	free(p);
}

void main()
{
	char *p = NULL;

	p = (char *)malloc(sizeof(char));
	myFree(p);

	return;
}