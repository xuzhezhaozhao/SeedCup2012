#include <stdlib.h>

void main()
{
	short *p = NULL;
	p = (short *)malloc(sizeof(unsigned short));
	
	if (NULL != p)
	{
		free(p);
	}
	p = NULL;
	
	return;
}