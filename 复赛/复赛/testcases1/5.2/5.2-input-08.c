#include <stdlib.h>
#define FIVE 5

void main()
{
	char *p = NULL;
	p = (char *)malloc(sizeof(unsigned long));
	*p = FIVE;
	free(p);
	p = NULL;
	return;
}