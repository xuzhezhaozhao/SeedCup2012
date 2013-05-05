#define TEN 10

int func2()
{
    return TEN;    
}
#define FUNC2() (func2() + TEN)

int func(int iNum)
{    
    iNum = 0;
    iNum = FUNC2();
    return func2();     
}

int main()
{   
    int iNum = 0;
    
    iNum = func(iNum);
    
    return 0;
}
