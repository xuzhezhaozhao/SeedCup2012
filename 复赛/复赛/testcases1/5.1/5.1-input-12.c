#define PI 3.14

int func2(long a)
{
    return a == PI;
}

int main()
{
    long b=PI;
    int res;

    res = func2(b);
  
    return 0;
}
