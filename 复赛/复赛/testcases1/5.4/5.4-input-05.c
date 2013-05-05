
int main()
{  
    unsigned short usNum = 0;
    static float fa = 0;

    do
    {
        fa += 3;
    }while(sizeof(usNum) > fa);
    
    return 0;
}
