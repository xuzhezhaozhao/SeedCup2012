#include <stdio.h>

#define TWO 2

int main()
{  
    int i = 0;
    int j = 0;
    
    i = getchar();
    
    switch(i)
    {
        case 1:
        {
            j = -1;
            break;    
        }
        
        case TWO:
        {
             j = 1;
             break;
        }     
        
        default:
        {
            j = 0;
            break;
        }   
    }
    
    return 0;
}
