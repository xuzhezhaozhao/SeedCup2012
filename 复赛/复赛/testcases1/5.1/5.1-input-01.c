/* right if,int case */
#define TMPNUM 123
#include<stdio.h>
int main()
{
	char iTmp;
	iTmp = getchar();
	
	if(TMPNUM == iTmp)
		iTmp++;
		
	return 0;
}
