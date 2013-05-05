int func1(int a)
{
    return a;
}

#define SUM(a,b) func1(a+b)

int main()
{
    SUM(1,2);
    return 0;
}
