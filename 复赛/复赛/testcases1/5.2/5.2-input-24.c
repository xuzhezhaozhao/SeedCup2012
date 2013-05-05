#include <stdlib.h>
#include <stdio.h>

static int *p = NULL;

void fun1()
{
	p = (int *)malloc(sizeof(int));

}

void fun2()
{
	free(p);
}

void main()
{
	fun1();
	fun2();
	return;
}