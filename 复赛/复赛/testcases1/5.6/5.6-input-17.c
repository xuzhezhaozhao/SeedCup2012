#define FUNC func3()

int func3()
{
    return -1;
}

int func2(int a)
{
    return a+a;
}

int func1(int b)
{
    return b^b;
}

int main()
{
    (void)func1(func2(FUNC));
    
    return;
}
