/* 实现5.3.1功能：无效分支之if语句 */

#ifndef _5_3_1_H_
#define _5_3_1_H_

using namespace std;

//检测无效的while分支
void ifErr();

//情况一：表达式为true或false
void if1();

//情况二：表达式为纯数字运算式 如"-1+(2*3/5)", 可以有大中小括号
void if2();

//情况三：表达式中只有一个变量，而且该变量是值在之前赋值为定值了
void if3();

//功能：情况三考虑在一个函数中的情况
int ifFunc3(int begin);

//功能：得到一条语句中的变量名,保存到数组中
//参数：begin指明从哪里开始查找函数
//返回值：变量名的个数
int getVarFromOneCmd(int begin, string cmd, string oneCmdVarName[]);
#endif