void func2()
{
}

void func1()
{
    func2();
}

int main()
{
    int i;

    for (i = 10; i > 0; i ++)
    {
        func1();
    }
    return 0;
}
