void func1();
void func2();

int g_c = 0;

void func1()
{
    if (0 == (g_c % 1))
    {
        func2();
    }
}

void func2()
{
    if (1 == (g_c % 1))
    {
        func1();
    }
}

int main()
{
    g_c = 2;

    func1();
    return 0;
}
