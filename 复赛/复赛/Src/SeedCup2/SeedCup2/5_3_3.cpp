/* 实现5.3.3功能：无效分支之switch语句*/

#include"SeedCup2.h"

//功能：检测无效的switch分支
void switchErr()
{
	int begin = 0;
	while(-1 != begin)
	{
		begin = switchInfunc(begin);
	}
}

//功能：得到一个函数中的从指定位置查找到的一个switch语句语句的所有相关命令到数组中
//参数：begin是从函数的第几行开始查找，switchLen是switch语句的长度
//返回值：返回这个switch结尾下一行减1
int getOneSwitch(string func[], int flen, int begin, string switchCmd[], int & switchLen)
{
	int i=0;
	int j=0;
	int k=0;
	switchLen = 0;
	string single[100] = {""};
	string temp = "";
	int slen = 0;
	int bracket = 0;  // 大括号匹配检测

	for(i=begin; i<flen; i++)
	{
		temp = func[i];
		slen = covertCmd(temp, single);

		if("switch" == single[0] && ";" != single[slen-1]) // 判断是否是switch语句的开始
		{
			// switch语句的开始，操作完成后就要break出语句
			bracket = 0;  //大括号匹配值初始为0
			j = 0;
			for(k=i; k<flen; k++)
			{
				switchCmd[j] = func[k];   // 先将该行赋给switchCmd[j]
				switchLen = j+1;
				j++;
				temp = func[k];
				slen = covertCmd(temp, single);

				if(k == i && "}" == single[slen-1])
				{
					return (k+1);
				}
				else
				{
					getBracket(single, slen, bracket); // 得到大括号匹配情况

					if(k!=i && 0 == bracket)   // 大括号匹配完成，说明switch语句结束
					{
						return (k+1);
					}
					else // 没有匹配结束，说明switch语句还没有结束
					{
						continue;
					}
				}
			}
		}
	}

	return -1;
}

//功能：在一个函数中检测无效的switch语句
//返回值：返回函数结尾下一行减1
int switchInfunc(int beginFunc)
{
	string func[255] = {""};
	int flen = 0;
	int rowNum = getFunc(func, beginFunc, flen);	

	int i, j, k;
	if(-1 != rowNum)
	{
		int	useFlag = -1;
		int varEqualNum = 0;

		string switchValue = "";  // switch 的值

		string temp = "";
		string single[255] = {""};
		int slen = 0;
		string oneCmdVarName[255] = {""};
		int oneCmdVarLen = 0;
		string switchCmd[255] = {""};
		int switchLen = 0;
		int beginInfunc = 0;

		int pos[10] = {-1};
		int posCount = -1;
		for(i=0; i<flen; i++)
		{
			temp = func[i];
			slen = covertCmd(temp, single);
			if(isIn("switch", single, slen)) //在函数第i行位置 检测到switch语句
			{
				beginInfunc = i;
				int switchPos = getOneSwitch(func, flen, beginInfunc, switchCmd, switchLen); // 得到第一个switch语句
				temp = switchCmd[0];  // switch
				slen = covertCmd(temp, single);
				oneCmdVarLen = getVarFromOneCmd(beginFunc, switchCmd[0], oneCmdVarName);// 得到switch中的变量名
				if(1 == oneCmdVarLen)  //switch中只有一个变量时
				{
					for(j=0; j<oneCmdVarLen; j++)    // 遍历switch中所有变量
					{
						useFlag = -1;
						varEqualNum = 0;
						for(k=i-1; k>=0; k--)   // 在switch语句之前进行检测变量的赋值情况
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
										switchValue = single[pos[m]+2]; // 得到switch的值
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
					int defaultFlag = -1;
					if(-1 == useFlag)  // 说明一直没有变量变，无效分支
					{
						defaultFlag = -1;
						for(k=0; k<switchLen; k++)
						{
							temp = switchCmd[k];
							slen = covertCmd(temp, single);
							if(isIn("case", single, slen))  // 出现case 分支
							{
								if(switchValue != single[1]) // 当这一行的case值不是switch的时候则报错
								{
									errNum[errLen] = (rowNum-flen+i+1+k);
									errType[errLen] = 3;
									errLen++;
								}
								else   // case值是switch值时，说明default也要报错
									defaultFlag = 1;
							}
						}
						for(k=0; k<switchLen; k++)
						{
							temp = switchCmd[k];
							slen = covertCmd(temp, single);
							if(isIn("default", single, slen) && 1 == defaultFlag)  // 出现case 分支
							{
								errNum[errLen] = (rowNum-flen+i+1+k);
								errType[errLen] = 3;
								errLen++;
							}
						}
					}
				}//switch中只有一个变量时
				
				int defaultFlag = -1;
				if(0 == oneCmdVarLen)  // 说明switch里面没有变量
				{
					temp = switchCmd[0];
					slen = covertCmd(temp, single);
					if(onlyNum(single[2]) && ")" == single[3])   // switch(1) 的形式
					{
						switchValue = single[2];
						defaultFlag = -1;
						for(k=0; k<switchLen; k++)
						{
							temp = switchCmd[k];
							slen = covertCmd(temp, single);
							if(isIn("case", single, slen))  // 出现case 分支
							{
								if(switchValue != single[1]) // 当这一行的case值不是switch的时候则报错
								{
									errNum[errLen] = (rowNum-flen+i+1+k);
									errType[errLen] = 3;
									errLen++;
								}
								else   // case值是switch值时，说明default也要报错
									defaultFlag = 1;
							}
						}
						for(k=0; k<switchLen; k++)
						{
							temp = switchCmd[k];
							slen = covertCmd(temp, single);
							if(isIn("default", single, slen) && 1 == defaultFlag)  // 出现case 分支
							{
								errNum[errLen] = (rowNum-flen+i+1+k);
								errType[errLen] = 3;
								errLen++;
							}
						}
					}
				}
			}   // 检测到switch的位置
		}
	}
	return rowNum;
}