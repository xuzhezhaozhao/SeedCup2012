int func2(int a)
{
    return a;
}

int func1(int b)
{
    return b;
}

int main()
{
    return func2(func1(0));
}
