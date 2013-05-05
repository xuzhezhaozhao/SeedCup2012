#include <stdlib.h>

void main()
{
	char *p = NULL;
	p = (char *)malloc(sizeof(unsigned long));
	*p = 1;
	free(p);
	return;
}