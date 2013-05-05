#define TEN 10

int func2()
{
    return TEN - 1;    
}


int func(int iNum)
{   
    int ai[TEN];

    ai[func2()] = 0;
    
    return iNum;     
}

int main()
{   
    int iNum = 0;
    
    iNum = func(iNum);
    
    return 0;
}
