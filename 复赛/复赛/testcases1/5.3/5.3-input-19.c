#define A 123
#define B 234
#define C 345
int main()
{
	int a,b,c;
	
	a=(A/B+C)%A*B-C;
	b=A+B%(A+B/C)-C;
	
	c = a<b?a:b;
	
	return 0;
}
