#define TEN 10

int func2()
{
    return TEN;    
}


int func(int iNum)
{   
    func2();
    return iNum;     
}

int main()
{   
    int iNum = 0;
    
    iNum = func(iNum);
    
    return 0;
}
