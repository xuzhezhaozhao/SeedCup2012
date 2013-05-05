/* 
#define TEN 10 
*/

#define TEN 10
int func(int iNum);

int func(int iNum)
{
#define PROC() (func(1) + TEN)
    iNum = TEN;
     
    return iNum;     
}

int main()
{
    int iNum = 0;
    
    (void)func(iNum);
    
    return 0;
}
