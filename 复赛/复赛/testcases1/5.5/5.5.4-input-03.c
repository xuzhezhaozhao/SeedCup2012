#define TEN 10

int func2()
{
    return TEN;    
}


int func(int iNum)
{    
    iNum = 1;
    return func2();     
}

int main()
{   
    int iNum = 0;
    
    iNum = func(iNum);
    
    return 0;
}
