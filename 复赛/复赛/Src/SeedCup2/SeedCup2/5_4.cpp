/* 实现5.4的功能：魔鬼数字  */

#include"SeedCup2.h"

//功能：除#define命令外逐条命令检测魔鬼数字
void ghostNum()
{
	int i;
	string temp = "";
	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		if(!checkDef(temp))   // 如果不是#define语句，则需要判断是否含有魔鬼数字
		{
			checkNum(temp, i+1);  // 检查该条命令中的魔鬼数字
		}
	}
}

//功能：检测字符串被打散后的字符串中是否含有魔鬼数字
//参数：line是字符串的行数
void checkNum(string test, int line)
{
		int i;
		float temp = 0;
		string single[255] = {""};
		int slen = 0;
		slen = covertCmd(test, single);

		for(i=0; i<slen; i++)
		{
			if(onlyNum(single[i]))
			{
				temp = atof(single[i].c_str());
				if(0 != temp && 1 != temp)
				{
					errNum[errLen] = line;
					errType[errLen] = 4;
					errLen++;
				}
			}
		}
}

//功能：判断字符串是否只含有小数点或数字
//返回值：有的话返回true
bool isNum(string test)
{
	int len = test.size();
	int i;
	for(i=0; i<len; i++)
	{
		if('.' != test[i] && (test[i] >'9' || test[i]<'0'))
		{
			return false;
		}
	}

	return true;
}

//功能：检测一个字符串中是否只含有1个或不含有小数点
//返回值：是返回true
bool checkDot(string test)
{
	int i = 0;
	int dot = 0;
	for(i=0; i<test.size(); i++)
	{
		if('.' == test[i])
		{
			dot++;
		}
	}

	if(1 < dot)
	{
		return false;
	}
	else
		return true;

}

