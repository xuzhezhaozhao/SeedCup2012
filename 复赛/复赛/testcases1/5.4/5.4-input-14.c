#include <stdlib.h>

#define TEN 10

int g_num = 10;

void func(int inum)
{
    inum = 0;
    
    g_num = 0;     
}

int main()
{   
    int aiList[TEN + 1];
    int *piNum = NULL;
    
    piNum = aiList;
    
    piNum[sizeof(piNum)] = 0;
    
    (void) func(TEN);
    
    return 0;
}
