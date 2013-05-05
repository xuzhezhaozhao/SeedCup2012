#include <stdio.h>

int func1(int a)
{
    return a;
}

int func2(int b)
{
	return b;
}

int func3(int b)
{
	return b;
}

int main()
{
	char p;

	p =getchar();

	switch(p)
	{
	case 0:
		(void)func1(p);
		break;
	case 1:
	default:
		(void)func2(p);
	}

	return 0;
} 