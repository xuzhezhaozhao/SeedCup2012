
#define TEN 10

int func(int iNum)
{
    iNum = TEN;
     
    return iNum;     
}

#define PROC() (func(1) + TEN)

int main()
{
    int iNum = 0;
    
    (void)func(iNum);
    
    return 0;
}
