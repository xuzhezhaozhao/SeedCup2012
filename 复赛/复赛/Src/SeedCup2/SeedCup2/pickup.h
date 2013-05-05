#ifndef _PICK_UP_H_
#define _PICK_UP_H_

using namespace std;

// 功能：将与一个函数定义有关的命令行从command[]中取出，存入到func数组中，
//+ 从command[]的begin位置(0起始)开始查找函数，只读入找到的第一个函数，包括main函数
//+ 如 void func(){int i=1;
//+			int j=8;
//+		}  
//+ 将其按行存入func[]中,存入的是原始命令，没有经过处理
//返回值：返回读取的函数下一行行号减1的值,若之后没有找到函数则返回－1
//参数：begin查找起始位置，func_len是该函数的总行数
int getFunc(string func[], int begin,  int & func_len);

//功能：读取指定函数名的函数
void getFuncFromName(string func[], int & func_len, string funcName);

// 功能：将#define定义的宏名依次追加到def数组中,如#define MAX 100, 将MAX存入def
// 返回：返回宏个数
int getDefine(string def[]);

//功能：得到函数中的变量名，包括形参名
//参数：参数：begin查找起始位置，只查找找到的第一个函数
//返回值：变量个数
int getFuncVar(string funcVar[], int begin);

//功能：将一条变量声明语句(不含有const,sttic,signed,unsigned,extern开头)中的变量名赋给funVar[len]，len是原有的数组长度，这样可以保存原来的变量,
//+不能得到声明函数的形参名， 如int const**i, j, k, m;
void getVar1(string single[], int slen, string funcVar[], int & len);

//功能：类似getVar1,不过增加了识别signed 和 unsigned
void getVar2(string single[], int slen, string funcVar[], int & len);

//功能：类似getVar2,不过在其基础上增加了识别const开头的
void getVar3(string single[], int slen, string funcVar[], int & len);

//功能：类似getVar3,不过在其基础上增加了识别extern开头的
void getVar4(string single[], int slen, string funcVar[], int & len);

//功能：与getVar2()功能类似，不过在其基础上增加了识别声明函数的形参名，但返回值类型不包含const,[un]singed,extern,static，如 void func(signed int const* p1, float *const p2)
void getVar5(string single[], int slen, string funcVar[], int & len);

//功能：与getVar5()功能类似，不过在其基础上增加了返回值类型包含const,[un]singed,extern,static，如 static void func(signed int const* p1, float *const p2)
void getVar6(string single[], int slen, string funcVar[], int & len);

//功能：综合getVar,解析出一条命令中定义的参数名
void getVar(string cmd, string funcVar[], int & len);

//功能：得到全局变量名
//返回值：全局变量数组长度
int getGlobeVar(string globeVar[]);


//功能：得到全部的函数名及对应的返回值类型，0表示void,1表示其他，包括main函数
//返回值：数组长度
int getFuncName(string funcName[], int returnType[]);

//功能：得到函数定义语句中函数名及返回值类型，返回值类型保存在returnType中，0表示void, 1表示其他
//返回值：函数名
string getFuncStaName(string single[], int slen, int & returnType);

//功能：得到指定函数定义的位置(0起始)
//返回值：位置，不存在返回－1
int getFuncPosFromName(string funcName);

//功能：判断cmp的有没有在std中的元素，有的话追加存在get数组中
//参数：len1 std长度，len2 cmp长度, len3 get长度
void haveGet(string std[], int len1, string cmp[], int len2, string get[], int & len3);
#endif