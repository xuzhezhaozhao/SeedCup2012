#define FUNC()  10
#define func2()\
{\
    return func1(FUNC());\
}\

int func1(int a)
{
    return --a;
}
int main()
{    
    int i;
    int sum = 10;

    for (i = 0; i < (func1(sum)); i ++)
    {
        if (0 == i % 2)
        {
            return FUNC();
        }
        else
        {
            func2();
        }
    }
    
    return 0;
}
