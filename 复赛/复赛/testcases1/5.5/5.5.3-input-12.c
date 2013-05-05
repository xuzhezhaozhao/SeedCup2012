#include <stdio.h>
#define FIVE 5

char c;

int fun(int a, int b)
{
	return a++;
}

int main()
{
	int  i = 0;
	char d = 0;
	
	do
	{
		i = fun(i, c);
		d = getchar();
		if ('1' == d)
		{
			break;
		}

	}while(i < FIVE);

	return 0;
}