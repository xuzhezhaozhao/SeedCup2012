#ifndef _AUXILIARY2_H_
#define _AUXILIARY2_H_

using namespace std;

//功能：判断该行命令(行命令已经经过了字符串的转换了)是不是函数定义(不是声明)的开头，如void main()，len是字符串数组的有效长度
//返回值：是返回true
bool isFuncDef(string str[], int len);

//功能：判断该行命令(行命令已经经过了字符串的转换了)是不是函数声明(不是定义)，如"void myFunc();", len是字符串数组的有效长度
//返回值：是返回true
bool isFuncState1(string str[], int len);

//功能：判断该行命令(行命令已经经过了字符串的转换了)是不是函数声明(不是定义)，返回值类型包含const,[un]singed,extern,static，如"extern void myFunc();", len是字符串数组的有效长度
//返回值：是返回true
bool isFuncState(string single[], int slen);

//大括号匹配查询，如果single数组中的左大括号则bracket值加1，有右大括号则bracket值减1
void getBracket(string single[], int len, int & bracket);

//小括号匹配查询，如果single数组中的左小括号则bracket值加1，有右小括号则bracket值减1
void getLittleBracket(string single[], int len, int & bracket);

//待检字符串是否是数据类型关键字
bool isType(string test);

//功能： 指定字符串数组中是否存在指定字符串，len为数组长度，pos[]数组保存字符串出现的位置
//返回值：不存在返回－1，存在则返回该字符串出现次数
int isContain(string str,string contain[], int len, int pos[]);

//指定字符串数组中是否存在指定字符串, 不区分大小写，len为数组长度，存在则返回true，不存在返回false
bool isIn(string str,string contain[], int len);

//功能：得到一个字符串在文件出现的次数
//返回值：次数
int getCount(string test);

//功能：检测字符串是否是#define命令
//返回值：是返回true
bool checkDef(string test);

//功能：按两个比较级排序，先按one排序，one相同则按two排序
//参数：两个数组长度相同，为len
void sortTwo(int one[], int two[], int len);


//功能：检测字符串是否是数字
//返回值：是的话返回true,不是的话返回false
bool onlyNum(string test);

#endif