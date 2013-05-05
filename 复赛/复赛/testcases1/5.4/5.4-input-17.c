#define TEN 10

int func(char *piTemp)
{
    piTemp[5] = 'a';
    return TEN;
}

int main()
{
  char szTemp[10];
  
  szTemp[0] = '\0';
  (void)func(szTemp);
  
  
  return 0;
}
