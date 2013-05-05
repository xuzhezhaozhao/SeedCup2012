#define TMP 123

int func()
{
	return TMP;
}
void main()
{
	int i;
	
	if(TMP==(i=func()))
		i--;
		
	return;
}
