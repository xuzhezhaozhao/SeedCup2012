void main()
{
	int *p;
	int a;
	
	p = (int*)malloc(sizeof(int));
	*p = 1;
	free(p);
	p = NULL;
	
	if(NULL == p)
		a=1;
	else
		a=0;
}
