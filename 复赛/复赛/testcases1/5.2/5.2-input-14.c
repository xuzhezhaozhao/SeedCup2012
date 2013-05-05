
#include <stdlib.h>
#include <stdio.h>

#define RAND 80

void main()
{
	char *p = NULL;
	unsigned int i = 0;
	
	for (i = 0; i < RAND ; i++)
	{
		p = (char *)malloc(sizeof(char));
		if (NULL != p)
		{
			break;
		}
	}
	
	free(p);
	return;
}