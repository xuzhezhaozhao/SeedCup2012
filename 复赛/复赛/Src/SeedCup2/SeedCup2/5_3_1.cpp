/* 实现5.3.1功能：无效分支之if语句 */

#include"SeedCup2.h"

//检测无效的if分支
void ifErr()
{
	if1();
	if2();
	if3();
}

/* 先考虑表达式中不含就是的情况 */
//情况一：表达式为true或false
void if1()
{
	int i;
	string temp = "";
	string single[255] = {""};
	int slen = 0;
	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		slen = covertCmd(temp, single);
		int pos[10] = {0};
		int posCount = isContain("if",single, slen, pos);
		if(-1 != posCount)  // 含有关键字if
		{
			if(("true" == single[pos[0]+2] || "false" == single[pos[0]+2]) && ")" == single[pos[0]+3])
			{
				errNum[errLen] = i+1;
				errType[errLen] = 3;
				errLen++;
			}
		}
	}
}

//情况二：表达式为纯数字运算式 如"-1+(2*3/5)", 可以有大中小括号
void if2()
{
	int i, j;
	string temp = "";
	string single[255] = {""};
	int slen = 0;
	int numFlag = 1;  // 是否为纯数字运算的标志, 是为1，不是为－1
	for(i=0; i<cmdCount; i++)
	{
		numFlag = 1;
		temp = command[i];
		slen = covertCmd(temp, single);
		int pos[10] = {0};
		int posCount = isContain("if",single, slen, pos);
		if(-1 != posCount)  // 含有关键字if
		{
			for(j=pos[0]+1; j<slen; j++) // 遍历if后的所有字符，看是否是纯数字表达式
			{
				if("(" != single[j] && ")" != single[j] && "[" != single[j] && "]" != single[j] &&
					"{" != single[j] && "}" != single[j] &&
					"+" != single[j] && "-" != single[j] && "*" != single[j] && "/" != single[j]
					&& !onlyNum(single[j]))     // 纯数字表达式可能出现的字符, 满足所有条件时不是纯数字
				{
					numFlag = -1;
					break;
				}
			}
			if(1 == numFlag)
			{
				errNum[errLen] = i+1;
				errType[errLen] = 3;
				errLen++;
			}
		}
	}
}


/*考虑表达式中含有变量的情况*/

//情况三：表达式中只有一个变量，而且该变量是值在之前赋值为定值了
void if3()
{
	int begin = 0;
	while(-1 != begin)
	{
		begin = ifFunc3(begin);
	}
}

//功能：情况三考虑在一个函数中的情况，判断思想是找到if语句中所有的变量名，然后在if语句之前往上查找，如果最后一次出现该变量时是
//+"a=常数"的情况，如果最后是"a>、<、>=、<=、!=、+、-、*、/"的情况就跳过继续往上查，则判断为该变量是不变的，不过这样会有很多的bug，待解决啊……
int ifFunc3(int begin)
{
	string func[255] = {""};
	int flen = 0;
	int rowNum = getFunc(func, begin, flen);	

	int i, j, k;
	if(-1 != rowNum)
	{
		int varEqualNum = 0;
		int useFlag = -1;

		string single[255] = {""};
		int slen = 0;
		string temp = "";

		string oneCmdVarName[255] = {""};
		int cmdVarLen = 0;

		int pos[10] = {-1};
		int posCount = -1;
		for(i=0; i<flen; i++)
		{
			temp = func[i];
			slen = covertCmd(temp, single);

			if(isIn("if", single, slen))  // 在func[i]中检测到if语句
			{
				cmdVarLen = getVarFromOneCmd(begin, temp, oneCmdVarName);  // 得到if条件中变量名

				for(j=0; j<cmdVarLen; j++)    // 遍历if中所有变量
				{
					useFlag = -1;
					varEqualNum = 0;
					for(k=i-1; k>=0; k--)   // 在if语句之前进行检测变量的赋值情况
					{
						temp = func[k];
						slen = covertCmd(temp, single);
						posCount = isContain(oneCmdVarName[j], single, slen, pos);
						int m = 0; // 变量在一行中出现的次数遍历
						if(-1 != posCount)   // 如果出现了变量, 检测最后出现变量的位置是不是a=1的简单形式
						{
							for(m=posCount-1; m>=0; m--) // 从一行最后开始遍历变量
							{
								//single[pos[m]+1] 变量后的第一个字符
								if(">" == single[pos[m]+1] || "<" == single[pos[m]+1] || ">=" == single[pos[m]+1] || 
									"<=" == single[pos[m]+1] || "!=" == single[pos[m]+1] || "+" == single[pos[m]+1] || "-" == single[pos[m]+1] ||
									"*" == single[pos[m]+1] || "/" == single[pos[m]+1])
								{
									continue;
								}
								if("=" == single[pos[m]+1] && onlyNum(single[pos[m]+2])) // a = 数字 的情况
								{
									varEqualNum = 1;
									break;
								}
								else
								{
									varEqualNum = -1;
									break;
								}
							}
							if(1 == varEqualNum || -1 == varEqualNum) // 如果continue了就要继续找下一行，而不是退出for循环
								break;
						}	
					}

					if(-1 == varEqualNum)
					{
						// 说明有变量会变
						useFlag = 1;
						break;   // 不是无效分去
					}
				}

				if(-1 == useFlag)  // 说明一直没有变量变，无效分支
				{
					errNum[errLen] = rowNum-flen+i+1;
					errType[errLen] = 3;
					errLen++;
				}
			}
		}
	}

	return rowNum;
}

//功能：得到一条语句中的变量名,保存到数组中
//参数：begin指明从哪里开始查找函数
//返回值：变量名的个数
int getVarFromOneCmd(int begin, string cmd, string oneCmdVarName[])
{
	int cmdVarLen = 0;

	string func[255] = {""};
	int flen = 0;
	int rowNum = getFunc(func, begin, flen);

	string funcVarName[255] = {""};
	int vlen = 0;
	vlen = getFuncVar(funcVarName, begin);  // 得到函数的所有变量名

	string globeVarName[255] = {""};
	int glen = 0;
	glen = getGlobeVar(globeVarName);

	string single[255] = {""};
	int slen = 0;
	slen = covertCmd(cmd, single);
	for(int i=0; i<slen; i++)
	{
		if(isIn(single[i], funcVarName, vlen) || isIn(single[i], globeVarName, glen))  // 如果single[i]是变量名
		{
			oneCmdVarName[cmdVarLen] = single[i];
			cmdVarLen++;
		}
	}

	return cmdVarLen;
}
