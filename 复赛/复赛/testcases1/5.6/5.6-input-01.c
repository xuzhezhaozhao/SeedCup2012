void func3()
{
	return;
}

void func2()
{
    func3();
}

void func1()
{
    func2();
}

int main()
{
    func1();
    func2();
    func3();
    return 0;
}
