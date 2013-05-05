/* test extern short, do ,while,sizeof */
#include<stdio.h>
#define SIZE 3

extern short a;
int main()
{
    int iSize;
    char b;
    b=getchar();
    do
    {
        iSize = sizeof(a)+b;
    }while(SIZE == iSize);

    return 0;
}
