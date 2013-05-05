#define LOW 2
#define HIGH 5
#define PI 3.14

int main()
{
    const double a=PI;
    int b=0;

    for(;a<LOW&&a>HIGH;b++)
    {
        if(b<HIGH)
          break;
        else
          continue;
    }
		
	return 0;
}


