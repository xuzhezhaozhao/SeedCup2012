#define PI 3.1415
#define TMP 'a'
int main()
{
    unsigned char a;
    signed float b;
    a = TMP;

    switch('a' == a)
    {
        case 0:
            b = PI;
            break;
        case 1:
            b = PI+1;
            break;
        default:
            break;
    }
 
    return 0;
}
