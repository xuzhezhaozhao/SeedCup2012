void func1();

void func2()
{
    func1();
}

void func1()
{
    func2();
}

int main()
{
    func1();
    return 0;
}
