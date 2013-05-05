/* right const double,for*/
#define PI 3.14
#include<stdio.h>
int main()
{
    const double a;

    a = getchar();
    for(;PI == a;)
    {
        if(a)
            break;
        else
            continue;
    }

    return 0;
}
