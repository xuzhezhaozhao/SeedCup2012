#include <stdlib.h>

#define TEN 10

void func(int iNum)
{
    iNum = TEN;
     
    return;     
}

int main()
{
    int iNum = 0;
    
    func(iNum);
    
    return 0;
}
