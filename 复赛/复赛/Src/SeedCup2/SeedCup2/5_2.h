/* 实现5.2功能：指针归空 */


#ifndef _5_2_H_
#define _5_2_H_

using namespace std;

//功能：对所有函数进行归空检测
void assignNull();

//功能：仅仅对begin位置后的第一个函数进行归空检测
//返回值：返回函数结尾的下一行行号减1的值，－1表示没有找到函数，
int funcAssignNull(int begin);

//功能：如果在函数func的pos行 位置出现的free(check_p),那么在该函数作用域内从pos+1行开始检测是否有check_p = NULL操作
//参数：func[] 保存函数行的数组， flen 函数行数组长度， pos 出现free的位置（相对函数数组），check_p free的指针
//返回值：true 表示有归空操作
bool checkNull(string func[], int flen, int pos, string check_p);


#endif