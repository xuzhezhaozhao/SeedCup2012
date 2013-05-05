
/*
#define THREE  3
*/

#define LOOP(iCur ,Times) for(iCur = 1; iCur < Times; iCur ++)

#define TEN   10

int func(int iNum)
{
    int i = 1;
    int iTemp = 0
    
    for (i = 1; i< iNum; i++)
    {
        iTemp += 1;
    }
     
    return iTemp;     
}

int main()
{   
    int iNum = 0;
    
    func(iNum);
    
    return 0;
}
