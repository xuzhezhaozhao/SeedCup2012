#include <stdio.h>
#define RAND1 40
#define RAND2 80

void func1()
{
    return;
}

void func2()
{
	return;
}

void func3()
{
	return;
}

void main()
{
	char a;
	a = getchar();

	if (a < RAND1)
	{
		func1();
	}
	else if (RAND1 < a < RAND2)
	{
		func2();
	}
	else
	{
		return;
	}
} 