#include <stdlib.h>
#include <stdio.h>

void fun(double **p)
{
	*p = NULL;
}

void main()
{
	double *p = NULL;

	p = (double *)malloc(sizeof(double));

	free(p);

	fun(&p);

	return;
}