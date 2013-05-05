#include <stdlib.h>

void FREE(void **p)
{
	free(*p);
	p = NULL;
}

int main()
{
	int *p = (int *)malloc(sizeof(int));
	FREE(p);
	return 0;
}