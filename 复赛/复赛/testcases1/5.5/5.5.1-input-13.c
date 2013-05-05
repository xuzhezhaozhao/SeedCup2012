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
	do
	{
		i = func2(i);
		i++;
		if (0 == i)
		{
			continue;
		}
	}while(i < 1);
	
	return func1(i);
} 