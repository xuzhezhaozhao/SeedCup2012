#include <stdlib.h>

#define TEN 10

int main()
{   
    int aiList[TEN + 1];
    int *piNum = NULL;
    
    piNum = aiList;
    
    piNum[sizeof(piNum)] = 0;
    
    return 0;
}
