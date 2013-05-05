#include <stdlib.h>

void main()
{
	short *p = NULL;
	p = (short *)malloc(sizeof(long));
	free(p);
	p = NULL;
	free(p);
	return;
}