#define THREE 3
#define SUM(a,b) a>>b  
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
    return (((SUM(1, 1)) - func1(THREE)) > func2(THREE)) ? THREE:FUNC;
}
