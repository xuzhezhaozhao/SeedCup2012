/* test for */
#define TMP 123
#define TMP2 234
int main()
{
	int a=TMP,b=TMP2,iTmp;
		
	for(;TMP == (iTmp=a>b?a:b);)
    {
    	iTmp++;
        break;
    }
		
	return 0;
}
