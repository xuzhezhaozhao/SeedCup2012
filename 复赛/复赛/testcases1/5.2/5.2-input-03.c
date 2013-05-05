#include <stdlib.h>

void main()
{
	double *p = NULL;
	free(p);
	p = NULL;
	return;
}