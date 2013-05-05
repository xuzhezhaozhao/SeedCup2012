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
	for (i = -1; 1 != i; i++ )
	{
		(void)func2(i);
		if (0 < func1(i))
		{
			break;
		}
	}
	return 0;
} 