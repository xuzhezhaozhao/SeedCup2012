#define THREE 3

int func()
{
    return 20;
}

int main()
{
  int iTemp = 0;
  int iTempS = 30;
  
  for (iTemp = 1; iTemp < 100; iTemp++)
  {
      iTempS = func();
      while (iTempS > 5)
      {
            iTempS = iTempS - THREE;
      }
  }
  
  return 0;
}
