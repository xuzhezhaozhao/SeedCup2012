#include <stdlib.h>
#include <stdio.h>

int * fun()
{
	int * p = (int *)malloc(sizeof(int));
	return p;
}

void main()
{
	int a, *p = fun();
	a = *p;
	return;
}