#define THREE 3

#define FOR_LOOP(iTemp, iTimes)  for (iTemp = 1; iTemp < iTimes; iTemp++)

int func()
{
    return 20;
}

int main()
{
  int iTemp = 0;
  int iTempS = 30;
  
  FOR_LOOP(iTemp, 100)
  {
      iTempS = func();
      while (iTempS > 5)
      {
            iTempS = iTempS - THREE;
      }
  }
  
  return 0;
}
