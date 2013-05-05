int func1(int a)
{
    return a;
}

int func2(int b)
{
	return b;
}

int func3(int c)
{
	return c;
}

int main()
{
	return func1(func2(func3(0)));
} 