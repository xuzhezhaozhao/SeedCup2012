#define TEN 10
void func3();

void func4()
{
  int iTemp = -1;
  
  iTemp = 10; 
  
  func3();    
}

void func3()
{
  int iTemp = -1;
  
  iTemp = 10;     
}

void func2()
{
  int iTemp = -1;
  
  iTemp = 10; 
  
  func4();    
}

void func1()
{
  int iTemp = -1;
  
  iTemp = 10; 
  
  func2();
  
  return;    
}

int main()
{
  int iTemp = 0;
  
  iTemp = 10;
  
  func1();
  
  iTemp = TEN;
  
  return 0;
}
