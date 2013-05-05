/* right static long,do,continue,while case */
#define PI 3.14

void func(long *b)
{
    static long a=PI;
    a++;
    *b = a;
}

int func2(long a)
{
    return PI == a;
}

int main()
{
    long b;
    int res;

    func(&b);
    res = func2(b);
  
    return 0;
}
