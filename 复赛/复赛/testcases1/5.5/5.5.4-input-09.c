#define TEN 10

int func2()
{
    return TEN;    
}


int func(int iNum)
{   
    #define FUNC() func2() + 1
    (void)func2();
    iNum = FUNC();
    return iNum;     
}

int main()
{   
    int iNum = 0;
    
    iNum = func(iNum);
    func2();
    
    return 0;
}
