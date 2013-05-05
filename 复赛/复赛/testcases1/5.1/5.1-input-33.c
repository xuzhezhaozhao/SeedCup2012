#define TMP 2
#include<stdio.h>

int main()
{
    char *a[TMP];
    int i=0;
        
    *a[i++] = getchar();
    a[i] = &getchar();
    i=0;
    if(TMP == *a[i++] ||
       *a[i] == TMP)
    {
        a[i] = i;
    }  

    return 0;
}
