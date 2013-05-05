#include <stdlib.h>
#include <stdio.h>

void main()
{
	char *a;
	char *p;

	a = (char *)malloc(sizeof(char));
	p = a;
	free(p);
	a = NULL;


	return;
}