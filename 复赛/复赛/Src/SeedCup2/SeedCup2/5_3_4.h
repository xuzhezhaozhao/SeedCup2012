/* 实现5.3.4功能：无效分支之for语句*/

#ifndef _5_3_4_H_
#define _5_3_4_H_

using namespace std;

//功能：检测无效的for循环
void forError();

//功能：检测一个函数中的for循环
//返回值:函数结尾下一行减1
int forErrorFunc(int begin);
#endif