/* 实现5.3.3功能：无效分支之switch语句*/

#ifndef _5_3_3_H_
#define _5_3_3_H_

using namespace std;

//功能：检测无效的switch分支
void switchErr();

//功能：得到一个函数中的从指定位置查找到的一个switch语句语句的所有相关命令到数组中
//参数：begin是从函数的第几行开始查找，switchLen是switch语句的长度
//返回值：返回这个switch结尾下一行减1
int getOneSwitch(string func[], int flen, int begin, string switchCmd[], int & switchLen);

//功能：在一个函数中检测无效的switch语句
//返回值：返回函数结尾下一行减1
int switchInfunc(int beginFunc);

#endif