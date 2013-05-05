#include <stdlib.h>


int fun(int a)
{
	return a;
}

#define FIVE 5

int main()
{
	int fun[FIVE] = {0};
	fun;
	return fun[0];
} 