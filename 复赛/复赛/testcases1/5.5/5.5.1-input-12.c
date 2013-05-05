int func1(int a)
{
    return a;
}

int func2(int b)
{
	return b;
}

int main()
{
	int i = -1;
	while( i < 1)
	{
		i = func2(i);
		i++;
		if (0 == i)
		{
			continue;
		}
	}
	return 0;
} 