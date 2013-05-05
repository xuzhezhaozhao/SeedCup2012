#define THREE 3
#define SUM(a,b) a>>b  
#define FUNC func3

int func3(int a)
{
    if (0 >= a)
    {
        return -1;
    }
    
    return FUNC(a);
}

int func2(int a)
{
    /*
        func1();
    */
    return func3(a*a);;
}

int main()
{
    func2(SUM(THREE,THREE));
    
    return 0;
}
