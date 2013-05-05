/* test extern short, do ,while,sizeof */
#include<stdio.h>
#define SIZE 3

extern short a;
int main()
{
    int iSize;
    int b;
    
    do
    {
        b=getchar();
        iSize = sizeof(a)+b;
    }while(iSize == SIZE);

    return 0;
}
