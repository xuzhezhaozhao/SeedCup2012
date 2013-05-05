#include <stdio.h>

#define TEN 10

int main()
{  
    double dnum = 0;
    int i = 0;
    int j = 0;
    unsigned long ulnum = 0;
    
    for (i = 0; i < sizeof(double); i++)
    {
        j = getchar();
        if (j < sizeof(long))
        {
            ulnum = 1;
        }
        else if (j < TEN)
        {
            dnum = -1;
            continue;
        }
        else
        {
            break;   
        }
    }
    
    return 0;
}
