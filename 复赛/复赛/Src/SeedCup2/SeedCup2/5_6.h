/* 实现5.6的功能: 函数关系调用图(简单及递归) */

#ifndef _5_6_H_
#define _5_6_H_

using namespace std;
/*
功能：根据第三步得出的二维图按要求的格式打印出函数调用图
*/
void getGraphic(string step[][100]);

/*
功能：第一步，仅仅先得到指定单个函数(不包含main函数)的调用关系, 如下形式, 表示f1调用f2和f3, 结果保存在一个二维数组step1[][100](有多少调用函数就有多少行)中
f1 f2
#  f3
返回值：二维数组行数，即调用函数个数
*/
int graphStep1(string funcName, string step1[][100]);

/*
功能：第二步，得到main函数的调用关系, 但main函数的维数应该更大，定义为100*100的，初始化为空
返回值：二维数组行数，即调用函数个数
*/
int graphStep2(string funcName, string step1[][100]);

/*
功能：第三步, 迭代，产生完整的二维函数调用图，其中"#"代表10个"-","*"表示空，标志递归的结束
返回值：二维图的行数
*/
int graphStep3(string step3[][100]);


//功能：得到指定函数调用的函数名，不检查重名，结果保存在funcName数组中
//返回值：数组长度
int getFuncName(string funcName[], string thisFuncName);

//功能：得到一条语句中的函数名, 结果追加存在funcNameFromCmd[]中, len是数组之前的长度
void getFuncNameFromCmd(string cmd, string funcNameFromCmd[], int & len);

//功能：去除字符串数组中重复的字符串,结果存放在clean[]中
//参数：len，test[]长度
//返回：clean长度
int delRepeat(string test[], int len, string clean[]);

//功能：对指定的string数组升排序，长度为len
void sortStringIncr(string str[], int len);

//功能：判断指定函数是否调用了其他函数
//返回值：调用了返回true, 没有调用返回false
bool isInvokeFunc(string funcName);

//功能：得到main函数二维调图第row行（0起始）未尾元素的值
//返回值：未尾字符串
string getMainEdge(int row, string step[][100]);

//功能：得到main函数二维调图第row行（0起始）未尾元素的列号（0起始）
//返回值：未尾列号
int getMainEdgeNum(int row, string step[][100]);


//功能：在main二维图未端插入新的拓补结构
//返回值：二维图的有效行数
int insertNewFunc(string step[][100], int stepLen, int row);

//功能：判断在row行是否产生了递归, 思想就是判断在该维上最后一个字符串是否和前面的相同，相同就是递归，
//+产生递归后将最后一个字符串的后一个字符串置为 "*",可以结束递归
void isRecursive(string step[][100], int row);

//功能：按要求转换二维图中的字符串，"#"变成10个"-", 函数名补齐，"*"转成空
void covertStep(string & str);
#endif