void func1();
void func2();
void func3();
void func4();
void func5();
void func6();
void func7();
void func8();
void func9();

void func1()
{
    func2();
}

void func2()
{
    func3();
}

void func3()
{
    func2();
}

void func4()
{
    func8();
}

void func5()
{
    func9();
}

void func6()
{
    func4();
}

void func7()
{
    func6();
}

void func8()
{
    func7();
}

void func9()
{
    func8();
    func1();
}

int main()
{    
    func9();
    return 0;
}
