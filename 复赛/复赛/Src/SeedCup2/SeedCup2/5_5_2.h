/* 实现5.5.2的功能：未使用的资源之：宏 */

#ifndef _5_5_2_H_
#define _5_5_2_H_

using namespace std;

//功能：处理无用宏
void uselessMacro();

//功能：得到宏定义语句中的宏名
//返回值：宏名
string getMacroName(string test);

//功能：得到一个宏在文件中使用的次数, "MAX;"、 、"MAX, 1"、"2, MAX, 1;"都不算使用了宏
//返回值：次数
int getMacroCount(string test);

#endif