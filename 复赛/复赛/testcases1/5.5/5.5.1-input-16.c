#include <stdlib.h>


const int *p = (int *)malloc(sizeof(long));
 
int main()
{
	return *p;
} 