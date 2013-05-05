/* right const double,for*/
#define PI 3.14
#include<stdio.h>
int main()
{
    const double a;
    a = getchar();
    for(;a == PI;)
    {
        if(a!=PI+1)
            break;
        else
            continue;
    }

    return 0;
}
