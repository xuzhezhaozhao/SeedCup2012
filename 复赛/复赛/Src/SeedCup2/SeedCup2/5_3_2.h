/* 实现5.3.2功能：无效分支之while语句(包括do...while) */


#ifndef _5_3_2_H_
#define _5_3_2_H_

using namespace std;

//检测无效的while分支
void whileErr();

//情况一：表达式为true或false
void while1();

//情况二：表达式为纯数字运算式 如"-1+(2*3/5)", 可以有大中小括号
void while2();

//情况三：表达式中只有一个变量，而且该变量是值在之前赋值为定值了
void while3();

//功能：情况三考虑在一个函数中的情况，判断思想是找到if语句中所有的变量名，然后在while语句之前往上查找，如果最后一次出现该变量时是
//+"a=常数"的情况，如果最后是"a>、<、>=、<=、!=、+、-、*、/"的情况就跳过继续往上查，则判断为该变量是不变的，不过这样会有很多的bug，待解决啊……
int whileFunc3(int begin);

#endif