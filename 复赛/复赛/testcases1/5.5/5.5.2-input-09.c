#define IN
#define OUT

int func(IN int a, OUT long b)
{
    return a+b;     
}

int main()
{       
    (void)func(0,1);
    return 0;
}
