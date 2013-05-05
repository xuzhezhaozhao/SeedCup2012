/* 实现5.5.1的功能：未使用的资源之：函数  */

#ifndef _5_5_1_H_
#define _5_5_1_H_

using namespace std;

//功能：处理未使用的函数
void uselessFunc();

//功能：处理未使用的函数资源, 当该函数有声明的情况
void uselessFunc1();

//功能：处理未使用的函数资源, 当该函数无声明，只有定义的情况
void uselessFunc2();

//功能：得到函数声明命令中的函数名
//返回值：得到的函数名
string getFuncName(string single[], int slen);

//功能：将有声明的函数的名保存在数组StaFuncName中
//返回值：数组长度
int getStaFuncName(string StaFuncName[]);


#endif