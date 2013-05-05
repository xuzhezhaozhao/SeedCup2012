#include <stdio.h>

void func2()
{
}

void func1()
{
    func2();
}

int main()
{
    func2();
    return 0;
}
