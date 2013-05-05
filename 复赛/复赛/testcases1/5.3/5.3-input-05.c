#include<stdio.h>
#define LOW 1
#define HIGH 5
extern short a;
int main()
{
    int iSize;
    
    do
    {
        iSize = sizeof(a);
        break;
    }while(iSize>LOW||iSize<HIGH);

    return 0;
}
