#define TMPNUM 123
#define FIVE 5
#include<stdio.h>
/* test array*/
void main()
{
	int a[FIVE];
	int i;
	
	for(i=0;i<FIVE;i++)
	{
		a[i] == i;
	}
		
	i = getchar();
    i %= FIVE;
	if(a[i] == TMPNUM)
		a[i]--;
		
	return;
}
