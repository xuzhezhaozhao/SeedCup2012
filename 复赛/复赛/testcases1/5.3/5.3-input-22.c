#define PI 3.1415
#define TMP 'a'
unsigned char a=TMP;
int main()
{
    signed float b;

    switch('a' == a)
    {
        case 1:
            b = PI+1;
            break;
        default:
            break;
    }
 
    return 0;
}
