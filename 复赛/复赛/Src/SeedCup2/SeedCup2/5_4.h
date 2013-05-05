/* 实现5.4的功能：魔鬼数字  */


#ifndef _5_4_H_
#define _5_4_H_

using namespace std;

//功能：除#define命令外逐条命令检测魔鬼数字
void ghostNum();


//功能：检测字符串被打散后的字符串中是否含有魔鬼数字
//参数：line是字符串的行数
void checkNum(string test, int line);

//功能：判断字符串是否只含有小数点或数字
//返回值：有的话返回true
bool isNum(string test);

//功能：检测一个字符串中是否只含有1个或不含有小数点
//返回值：是返回true
bool checkDot(string test);




#endif