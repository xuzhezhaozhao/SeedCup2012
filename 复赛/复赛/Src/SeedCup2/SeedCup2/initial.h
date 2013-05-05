#ifndef _INITIAL_H_
#define _INITIAL_H_

using namespace std;

//功能：读取命令到全局变量，并将注释置为空
void initial(string inputFile);

//功能：功能：读取指定文件的每行到全局变量command[]中保存，空行也算，cmdCount中保存读入命令的条数
void readFile(string inputFile);

//功能：将多行注释置为空
void delRowsAnnotation();

//功能：删除注释, 可以删除行间注释
void delAnnotation();

//功能：宏替换, 包含带参数和不带参数的情况
void macroReplace();

//功能：不带参数的宏替换，#define MAX (100*100)
void macroSimpleReplace();

//功能：带参数的宏替换
void macroComplexReplace();

//功能：得到带参数的宏的参数名，将其保存在macroVarName数组中
//参数：macro 宏定义语句
//返回值：参数个数
int getMacroVarName(string macro, string macroVarName[]);

//功能：判断一条语句是否是带参数的宏定义语句
//返回值：是返回true
bool isComplexMacroDef(string test);

//功能：如#define MAX(a, b) ((a)*(b))  得到((a)*(b)) 打散后的字符串数组
//参数：macro 宏定义语句
//返回值：数组长度
int getComplexMacroValue(string macro, string complexMacroValue[]);

//功能：得到使用带参的宏中的传递的值，如MAX(2, (3)) 中的2，(3)
//参数：macroName 宏名， useMacro 调用该宏的语句，macroVarLen 宏参个数
//返回值：返回将调用的宏打散后的字符串数组的长度
int getComplexMacroRealValue(string macroName, string useMacro, int macroVarLen, string macroRealValue[]);

//功能：展开单条调用了带参数的宏的语句
//参数：macroDef 宏定义语句， useMacro 调用语句，
//返回值：返回展开后的语句
string singleComplexMacroReplace(string macroDef, string useMacro);

//功能：删除字符串的双引号之间内容, 保留双引号
void delString(string & str);

//功能：删除读取到的代码中的双引号之间的内容
void delCmdString();

#endif