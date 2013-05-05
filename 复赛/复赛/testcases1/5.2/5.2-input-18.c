#include <stdlib.h>
#include <stdio.h>

void main()
{
	char **pp;
	pp = (char **)malloc(sizeof(char *));

	free(pp);
	*pp = NULL;

	return;
}