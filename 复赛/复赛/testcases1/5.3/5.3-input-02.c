#define LOW 2
#define HIGH 5
#define MID 4
#define PI 3.14

int main()
{
    unsigned char a=MID;
    signed float b;

    switch(a>LOW||a<HIGH)
    {
        case 1:
            b = PI;
            break;
        default:
            break;
    }
		
	return 0;
}

