#define TMP 3
#define FUNC()\
{\
    return TMP;\
}
#include<stdio.h>

int main()
{
    int a;
    a = getchar();

    if(a ==FUNC())
        a = TMP;

    return 0;
}
