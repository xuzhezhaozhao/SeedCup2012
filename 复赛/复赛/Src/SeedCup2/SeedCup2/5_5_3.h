/* 实现5.5.3的功能：未使用的资源之：变量 */

#ifndef _5_5_3_H_
#define _5_5_3_H_

using namespace std;

// 检测未使用的变量，包括局部、全局变量
void uselessVar();


//功能：检测全局变量是否使用
void uselessGlobeVar();

//功能：检测全局变量在函数中里否使用，还要考虑局部变量的影响
//参数：gfag初始为－1，如果变为了1,说明使用到了该全局变量
//返回值：函数结束行下一行减1，找不到函数则返回－1,
int isGlobeInFunc(string globeVar, int begin, int & gflag);

//功能：检测所有函数中未使用的变量
void uselessAllFuncVar();

//功能：检测一个函数中未使用的变量
//参数：函数查找的起始位置
//返回值：函数结束的下一行减1
int uselessFuncVar(int begin);

/*
功能：检测一个变量在函数是否用过, 如"int i; i;" 这样的不算用过
1.自己被改写
2.给其它变量赋值
3.间接决定其它变量数值. eg b = p[a]中的a
返回值：无用返回true, 有用则返回false
*/
bool isUselessFuncVar(string func[], int flen, string varName);

/*
功能：检测一个全局变量在函数是否用过
1.自己被改写
2.给其它变量赋值
3.间接决定其它变量数值. eg b = p[a]中的a
返回值：无用返回true, 有用则返回false
*/
bool isUselessGlobeVar(string func[], int flen, string varName);

//功能：得到变量名在函数中第一次出现的位置
//返回值：位置（0起始）,不存在返回－1
int getFirstAppearPos(string func[], int flen, string varName);

//功能：得到全局变量名第一次出现的位置
//返回值：位置（0起始）,不存在返回－1
int getGolbeVarPos(string cmd[], int len, string varName);
#endif