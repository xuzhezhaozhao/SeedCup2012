/*
实现自定义的功能: 
2、检测变量是否未赋初值就使用了
	如：int i;
		int j = i;
	报错位置：在声明变量的地方报错
	错误代码：8

	待改进：检查数组使用前是否赋初值还没有实现
*/
#include"SeedCup2.h"

//功能：检查所有函数的变量在使用前是否赋了初值，不检查全局变量
void noInitialVar()
{
	int begin = 0;
	while(-1 != begin)
	{
		begin = noInitialVarFunc(begin);
	}
	noInitialGolberVar();
}

//功能：检查一个函数中的变量在使用前是否赋了初值,基本思想就是检查一个变量第一次出现时其后是否是"=", 是的话就不再检查，不是的话就检查它第二次出现时其后是否是等"="
//返回值：函数结尾下一行行数减1
int noInitialVarFunc(int begin)
{
	int i, j, k;
	string func[255] = {""};
	int flen = 0;
	int rowNum = getFunc(func, begin, flen);
	if(-1 != rowNum)
	{
		string funcVarName[255] = {""};
		int vlen = getFuncVar(funcVarName, begin);

		string single[255] = {""};
		int slen = 0;

		int pos[10] = {-1};
		int posCount = -1;
		for(i=0; i<vlen; i++)  // 要考虑一行中多次出现变量的情况，如for语句中
		{
			int tempFlag = -1;   //变量是否赋值的标志
			for(j=0; j<flen; j++)
			{
				tempFlag = -1;
				slen = covertCmd(func[j], single);
				posCount = isContain(funcVarName[i], single, slen, pos);
				if(1 == posCount)   // 变量在该行出现一次
				{
					if("=" == single[pos[0]+1])  // j行变量声明时赋值了，不需要再检查
					{
						break;
					}
					else // 变量声明时没有赋值，继续检查，下次出现时一定要赋值
					{
						for(k=j+1; k<flen; k++)
						{
							slen = covertCmd(func[k], single);
							posCount = isContain(funcVarName[i], single, slen, pos);
							if(-1 != posCount)   // k行第二次出现变量
							{
								if("=" != single[pos[0]+1])   // 如果第二次没有赋值就报错
								{
									errNum[errLen] = (rowNum-flen+j+1);
									errType[errLen] = 8;
									errLen++;	
								}
								tempFlag = 1;
								break;   //第二次出现了变量就跳出
							}
						}
					}

					if(1 == tempFlag)
						break;
				}
			}   //遍历命令
		} //遍历变量名
	}
	return rowNum;
}

//功能：检查全局变量是否未赋初值就使用
void noInitialGolberVar()
{
	int i,j, k;
	string globeVar[255] = {""};
	int glen = getGlobeVar(globeVar);
	string single[255] = {""};
	int slen = 0;

	int pos[10] = {-1};
	int posCount = -1;
	for(i=0; i<glen; i++)  // 要考虑一行中多次出现变量的情况，如for语句中
	{
		int tempFlag = -1;   //变量是否赋值的标志
		for(j=0; j<cmdCount; j++)
		{
			tempFlag = -1;
			slen = covertCmd(command[j], single);
			posCount = isContain(globeVar[i], single, slen, pos);
			if(1 == posCount)   // 变量在该行出现一次
			{
				if("=" == single[pos[0]+1])  // j行变量声明时赋值了，不需要再检查
				{
					break;
				}
				else // 变量声明时没有赋值，继续检查，下次出现时一定要赋值
				{
					for(k=j+1; k<cmdCount; k++)
					{
						slen = covertCmd(command[k], single);
						posCount = isContain(globeVar[i], single, slen, pos);
						if(-1 != posCount)   // k行第二次出现变量
						{
							if("=" != single[pos[0]+1])   // 如果第二次没有赋值就报错
							{
								errNum[errLen] = j+1;
								errType[errLen] = 8;
								errLen++;	
							}
							tempFlag = 1;
							break;   //第二次出现了变量就跳出
						}
					}
				}

				if(1 == tempFlag)
					break;
			}
		}   //遍历命令
	} //遍历变量名
}