/* right unsigned char,switch,case,break case */
#define PI 3.1415
#include<stdio.h>
unsigned char a;
int main()
{
    signed float b;
    a = getchar();

    switch(a == 'a')
    {
        case 0:
            b = PI;
            break;
        case 1:
            b = PI+1;
            break;
        default:
            break;
    }
 
    return 0;
}
