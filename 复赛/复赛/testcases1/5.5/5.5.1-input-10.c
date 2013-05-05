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
	int i;
	for (i = -1; i != 1; i++ )
	{
		(void)func2(i);
	}
	return 0;
} 