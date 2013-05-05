/* 实现5.5.4的功能：未使用的资源之：返回值 */

#ifndef _5_5_4_H_
#define _5_5_4_H_

using namespace std;

//功能：检测每一个函数的调用函数是否用到函数返回值
void uselessReturn();

//功能：检测一个函数中的调用函数是否用到函数返回值
//返回值：函数结束下一行减1，没有函数则返回－1
int uselessReturnFunc(int begin);

//功能：根据函数名得到指定函数返回值类型，0：void 1:其他
//返回值：0，1
int getFuncType(string funcName);

//功能：判断cmp的有没有在std中的元素
//参数：len1 std长度，len2 cmp长度
//返回值：cmp中在std中最先出现的字符串,没有的话返回空字符串
string isHave(string std[], int len1, string cmp[], int len2);

//功能：判断出现malloc函数的地方是否利用了其返回值
void useReturnOfMalloc();
#endif