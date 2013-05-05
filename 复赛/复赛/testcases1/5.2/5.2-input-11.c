#include <stdlib.h>
#include <stdio.h>
#define TWO 2

void main()
{
	char *p = NULL;
	p = (char *)malloc(sizeof(unsigned char));
	
	*p = getchar();

	switch (*p)
	{
	case 1:
		*p = -1;
		break;
	case TWO:
		*p = 0;
		break;
	default:
		free(p);
		p = NULL;
	}
	
	return;
}