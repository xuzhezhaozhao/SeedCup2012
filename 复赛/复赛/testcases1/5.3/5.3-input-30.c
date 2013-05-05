#define TMP 3
#define FUNC()\
{\
    return TMP;\
}

int main()
{
    int a=TMP;

    if(FUNC() == a)
        a = TMP+1;

    return 0;
}
