#define THREE 3

int main()
{  
    unsigned short usNum = 0;
    static float fa = 0;

    do
    {
        fa += THREE;
    }while(sizeof(usNum) > fa);
    
    return 0;
}
