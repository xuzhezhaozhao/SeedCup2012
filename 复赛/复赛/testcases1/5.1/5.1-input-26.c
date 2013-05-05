/* test function*/
/* this is correct*/
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
	if(func()==i)
		i++;
		
	return 0;
}
