#define TEN 10

int func2(int a)
{
    return a;
}

#define ADD() func2(10)

int func(char *piTemp)
{
    piTemp[5] = 'a';
    return ADD();
}

int main()
{
  char szTemp[TEN];
  
  szTemp[0] = '\0';
  (void)func(szTemp);
  
  
  return 0;
}
