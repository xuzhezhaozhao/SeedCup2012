#define FIVE 5

int fun(int a, int b)
{
	return a++;
}

void main()
{
	int  i = 0;
	char c = 0;
	
	while(i < FIVE)
	{
		i = fun(i, c);
	}
}