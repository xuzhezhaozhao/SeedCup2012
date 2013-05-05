void func2();

#define FUN func2()

void func1()
{
    FUN;
}

void func2()
{
    printf("ok\r\n");
}

int main()
{
    func1();
    
    return 0;
}
