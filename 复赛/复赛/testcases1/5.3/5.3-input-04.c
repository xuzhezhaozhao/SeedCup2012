#define PI 3.14
#define LOW 2
#define HIGH 5
void func(long *b)
{
    static long a=PI;
    a++;
    *b = a;
}

int func2(long a)
{
    return a>LOW||a<HIGH;
}

int main()
{
    long b;
    int res;

    func(&b);
    if(func2(b))
		res=b;
  
    return 0;
}
