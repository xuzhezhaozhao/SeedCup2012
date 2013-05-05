
#define THREE 3
#define TEN   10

void func(int iNum)
{
    #define FOUR 4
    iNum = TEN;
     
    return;     
}

int main()
{
    int iNum = 0;
    
    func(iNum);
    
    return 0;
}
