static func2()
{
}

void func1()
{
    func2();
}

int main()
{
    char cNum;

    do
    {
        cNum = getchar();
        if ('a' != cNum)
        {
            continue;
        }
        else
        {
            break;
        }
    }while(1);

    switch (cNum)
    {
        case 'a':
        {
            func1();
            
            break;
        }
        default:
        {
            func2();
        }
    }
    
    return 0;
}
