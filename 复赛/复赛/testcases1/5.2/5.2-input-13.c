#include <stdlib.h>
#include <stdio.h>

#define RAND 80

void main()
{
	char *p = NULL;
	p = (char *)malloc(sizeof(unsigned char));
	
	while(*p > RAND)
	{
		*p = getchar();
	}
	p = NULL;
	
	return;
}