#include<stdio.h>
#define TMP 5
int main()
{
	int *piValue = (int)malloc(sizeof(int));
	
	*piValue = TMP;
	
	free(piValue);
	return 0;
}