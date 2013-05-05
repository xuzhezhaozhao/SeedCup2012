void func2()
{
}

void func1()
{
    func2();
}

int main()
{
    func1();
    func1();
    func2();
    func2();

    return 0;
}
