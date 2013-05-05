float func1(float a)
{
    return -a;
}

int func2(void *a)
{
    return *(int *)a;
}

int main()
{
    int a = 10;
    char *p = "test";
    
    func1((float)a);
    func2((void *)p);
        
    return 0;
}
