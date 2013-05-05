#include <stdlib.h>

#define TEST(XXX) free(XXX)

int main()
{
	int *p = (int *)malloc(sizeof(int));
	TEST(p);
	return 0;
}