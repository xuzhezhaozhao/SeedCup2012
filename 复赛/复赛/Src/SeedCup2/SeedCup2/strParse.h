// str_parse2.cpp中的函数声明
// 对读入的一行字符串进行处理，以方便后面的解析

#ifndef _STR_PARSE_
#define _STR_PARSE_ 

using namespace std;

//将字符串打散，分别按顺序分别存入在single数组中
int covertCmd(string & str, string single[]);

//在字符串中的符号（如>,<,分号,逗号,括号之类）前后加空格，$代表空格，即两边的字符串是一个字符串
void formatCmd(string & sentence);

// 在( ) [ ] { }, ; ' " : ? 字符前后加空格
void addBlank(string & sentence);

// 在'>','<','>=','<=', '!=', '==', '++', '--','+=', '-=', '*=', '/=', '||', '&&'前后加空格
void addBlank2(string & sentence);

//将"Who I am" 转成 "who$I$am"
void saveBlank(string & sentence);

//将字符串中的'$'置为' '空格
void encodeStr(string & cut);

//将以空格，制表符分隔的字符串依次放入single数组中，返回长度
int getSingle(string & str, string single[]);


#endif

