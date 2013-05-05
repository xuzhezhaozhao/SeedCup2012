/* 实现5.1的功能：防止错误赋值 */

#ifndef _5_1_H_
#define _5_1_H_

using namespace std;

//功能：对所有函数处理错误赋值
void errorAssign();

//功能：仅仅对begin位置后的第一个函数进行错误检测
//返回值：返回函数结尾的下一行行号减1的值，－1表示没有找到函数，
int funcErrorAssign(int begin);


#endif