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
	switch(i==func())
    {
        case 1:
            i++;
            break;
        default:
            break;
    }
		
	return 0;
}




