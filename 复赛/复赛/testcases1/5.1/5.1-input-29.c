/* test function*/
#define TMP 123
#include<stdio.h>
int func()
{
	return TMP;
}
int main()
{
	int i=0;
	i = getchar();
	while(i==func())
    {
        i++;
        break;
    }
		
	return 0;
}



