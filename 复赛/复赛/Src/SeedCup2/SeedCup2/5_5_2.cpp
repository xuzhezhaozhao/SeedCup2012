/* 实现5.5.2的功能：未使用的资源之：宏 */

#include"SeedCup2.h"


//功能：处理无用宏
void uselessMacro()
{
	int i=0;
	string temp = "";
	string single[255] = {""};
	string macroName = "";

	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		
		if(checkDef(temp)) // 如果是宏定义语句
		{
			macroName = getMacroName(temp);  // 得到宏名
			if(1 == getMacroCount(macroName))  // 宏出现次数等于1则是没有用过
			{
				errNum[errLen] = i+1;
				errType[errLen] = 5;
				errLen++;
			}
		}
	}
}

//功能：得到宏定义语句中的宏名
//返回值：宏名
string getMacroName(string test)
{
	string single[50] = {""};
	covertCmd(test, single);
	return single[1];
}


//功能：得到一个宏在文件中使用的次数, "MAX;"、 、"MAX, 1"、"2, MAX, 1;"都不算使用了宏
//返回值：次数
int getMacroCount(string test)
{
	int i;
	int count = 0; // 字符串出现的次数 
	string temp = ""; // 保存一条命令
	string single[255] = {""};
	int slen = 0;
	int posCount = 0;
	int pos[10] = {-1};
	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		slen = covertCmd(temp, single);
		posCount = isContain(test, single, slen, pos);
		if(-1 != posCount)  // 如果该行中含有该字符串
		{
			if(test == single[0] && ("," == single[1] || ";" == single[1]))  // MAX; MAX, 1;
			{
				count = count;
			}
			else
			{
				count = count + posCount;
			}
		}
	}

	return count;
}