#include <stdlib.h>

void fun()
{
	return;
}

void fun1()
{
	return;
}


#define FUNC fun

 
int main()
{
	FUNC();

	return 0;
} 