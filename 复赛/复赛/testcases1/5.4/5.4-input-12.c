#include <stdlib.h>

#define TEN 10

void func(int inum)
{
    inum = 0;
    
    return;     
}

int main()
{   
    int aiList[TEN + 1];
    int *piNum = NULL;
    
    piNum = aiList;
    
    piNum[sizeof(piNum)] = 0;
    
    func(sizeof(10));
    
    return 0;
}
