/* complex expression */
#define TMP 123
#include<stdio.h>
int main()
{
	int a,b,iTmp;
		
    a=getchar();
    b=getchar();
	if((iTmp=a>b?a:b) == TMP)
		iTmp++;
		
	return 0;
}
