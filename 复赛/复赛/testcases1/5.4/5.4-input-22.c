#define TEN 10

int main()
{
  int iTemp = 0;
  int iTempS = TEN;
  
  for (iTemp = 1; iTemp < 100; iTemp++)
  {
      iTempS = 10;
      while (iTempS > 5)
      {
            iTempS = iTempS - 3;
      }
  }
  
  return 0;
}
