#define TEN 10

int func2()
{
    return TEN;    
}


int func(int iNum)
{   
    (void)func2();
    return iNum;     
}
#define HAHA() (func(func(func2())))

int main()
{   
    int iNum = 0;
    
    iNum = func(func2());
    iNum = HAHA();
    
    return 0;
}
