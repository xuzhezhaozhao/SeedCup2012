/* 实现自定义的功能: 
1、检测内存是否泄漏
	1.1、malloc开了内存，没有free这块内存。
	1.2、用指针指向malloc开的内存，在没有释放这块内存之前改变了该的指针的值，使该块内存无法释放, 不动态跟踪free指针的值，如下
		int *p1 = (int)malloc(sizeof(int));
		int *p2 = (int)malloc(sizeof(int));	
		p1 = p2;
		free(p1);
	虽然p2的内存块由于p1的原因释放了，但是还是要在p2的声明处报错。

	报错位置：在malloc内存的位置
	错误代码：7
*/

#include"SeedCup2.h"

/*
功能：检测所有函数中的内存泄漏的情况
考虑到的情况：有指针指向该内存，没有free, malloc时无指针指向
*/
void memoryLeak()
{
	int begin = 0;
	while(-1 != begin)
	{
		begin = memoryLeakFunc(begin);
	}
	memLeakGlober();  // 全局变量的内存泄漏
}

//功能：检测一个函数中的内存泄漏问题
int memoryLeakFunc(int begin)
{
	int rowNum = memoryLeakFunc1(begin);
	memoryLeakFunc2(begin);

	return rowNum;
}

//功能：检测一个函数中的内存泄漏问题 1.1、malloc开了内存，没有free这块内存。
int memoryLeakFunc1(int begin)
{
	string func[255] = {""};
	int flen = 0;
	int rowNum = -1;
	rowNum =  getFunc(func, begin, flen);

	if(-1 != rowNum)   // 如果读取到了函数
	{
		int i, j;
		string temp = "";
		string single[255] = {""};
		int slen = 0;
		for(i=0; i<flen; i++)
		{
			temp = func[i];
			slen = covertCmd(temp, single);
			// 有"malloc"没有"="的情况
			if(isIn("malloc", single, slen) && !isIn("=", single, slen))  
			{
				errNum[errLen] = (rowNum-flen+i+1);
				errType[errLen] = 7;
				errLen++;
			}
			//有"malloc", 有"="的情况
			if(isIn("malloc", single, slen) && isIn("=", single, slen))
			{
				int freeFlag = -1;
				int pos[10] = {-1};
				int posCount = -1;
				posCount = isContain("=", single, slen, pos);
				string pFree = single[pos[0]-1];
				for(j=i+1; j<flen; j++)
				{
					temp = func[j];
					slen = covertCmd(temp, single);
					if(isIn("free", single, slen) && isIn(pFree, single, slen))  // free了pFree指向的指针
					{
						freeFlag = 1;
						break;
					}
				}
				if(-1 == freeFlag)   // 如果没有free
				{
					errNum[errLen] = (rowNum-flen+i+1);
					errType[errLen] = 7;
					errLen++;
				}
			}
		}

		return rowNum;
	}
	return -1;
}

//功能：检测一个函数中的内存泄漏问题 1.2、用指针指向malloc开的内存，在没有释放这块内存之前改变了该的指针的值，使该块内存无法释放.
//改变值的形式有指针－指针，指针－数组名，指针－变量取址（&）
int memoryLeakFunc2(int begin)
{
	string func[255] = {""};
	int flen = 0;
	int rowNum = -1;
	rowNum =  getFunc(func, begin, flen);
	string pointName[255] = {""};
	
	if(-1 != rowNum)   // 如果读取到了函数
	{
		int pointLen = getPointName(func, flen, pointName);

		int i, j, k;
		string temp = "";
		string single[255] = {""};
		int slen = 0;
		for(i=0; i<flen; i++)
		{
			temp = func[i];
			slen = covertCmd(temp, single);
			//有"malloc", 有"="的情况
			if(isIn("malloc", single, slen) && isIn("=", single, slen))
			{
				int freeFlag = -1;
				int pos[10] = {-1};
				int posCount = -1;
				posCount = isContain("=", single, slen, pos);
				string pFree = single[pos[0]-1];
				for(j=i+1; j<flen; j++)
				{
					temp = func[j];
					slen = covertCmd(temp, single);
					if(isIn("free", single, slen) && isIn(pFree, single, slen))
					{
						freeFlag = 1;
						break;
					}
					if(isIn(pFree, single, slen) && isIn("&", single, slen) && isIn("=", single, slen))
					{
						// 出现  p=&a; 的情况，改变指针的值
						errNum[errLen] = (rowNum-flen+i+1);
						errType[errLen] = 7;
						errLen++;
						break;
					}
					int tempFlag = -1;
					for(k=0; k<pointLen; k++)
					{
						int pos[10] = {-1};
						int posCount = -1;
						posCount = isContain(pFree, single, slen, pos);
						if(-1 != posCount)
						{
							if("=" == single[pos[0]+1])
							{
								if(pFree != single[pos[0]+2])   // 排除p1 = p1;的情况
								{
									// 出现p1 = p2, p1=a; 之类的情况, 而且还要pFree要在＝等号左边
									errNum[errLen] = (rowNum-flen+i+1);
									errType[errLen] = 7;
									errLen++;
									tempFlag = 1;
									break;
								}
							}
						}
					}
					if(1 == tempFlag)
					{
						break;
					}
				}
				
			}
		}
	}
	return rowNum;
}

//功能：得到函数中所有的指针变量名，包括数组名
//返回值：数组长度
int getPointName(string func[], int flen, string pointName[])
{
	int pointLen = 0;
	int i;

	string single[255] = {""};
	int slen = 0;
	int pos[10] = {-1};
	int posCount = -1;
	for(i=0; i<flen; i++)
	{
		slen = covertCmd(func[i], single);
		if(isType(single[0]))
		{
			posCount = isContain("*", single, slen, pos); // 指针
			if(-1 != posCount)
			{
				pointName[pointLen] = single[pos[0]+1];
				pointLen++;
			}
			posCount = isContain("[", single, slen, pos); // 数组
			if(-1 != posCount)
			{
				pointName[pointLen] = single[pos[0]-1];
				pointLen++;
			}
		}
	}
	return pointLen;
}

//功能：得到全局变量中的指针变量名，数组变量名
//返回值：数组长度
int getGloblePointName(string globePointName[])
{
	int i;
	string temp = "";
	string single[255] = {""};
	int slen = 0;

	int glen = 0; //全局变量数组长度
	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		slen = covertCmd(temp, single);

		if(!isFuncDef(single, slen))   // 碰到第一个函数定义说明之后没有全局变量的声明了
		{
			if(isIn("*", single, slen) || isIn("[", single, slen))  // 含"*"或"["说明有指针或数组
			{
				getVar(temp, globePointName, glen);
			}
		}
		else
		{
			break;
		}
	}
	return glen;
}

//功能：得到全局变量中开了内存的指针名
//返回值：数组长度
int getGloberMalloc(string globeMallocName[])
{
	int i;
	string temp = "";
	string single[255] = {""};
	int slen = 0;

	int glen = 0; //全局变量数组长度
	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		slen = covertCmd(temp, single);

		if(!isFuncDef(single, slen))   // 碰到第一个函数定义说明之后没有全局变量的声明了
		{
			if(isIn("*", single, slen) && isIn("malloc", single, slen))  // 含"*"和"malloc"说明开了内存
			{
				getVar(temp, globeMallocName, glen);
			}
		}
		else
		{
			break;
		}
	}
	return glen;
}

//功能：检查全局变量开的内存是否释放，不考虑局部变量覆盖的影响
void memLeakGlober()
{
	int i, j;
	int memLeakFlag = -1;  // 有泄漏就是－1
	string globeMallocName[255] = {""};
	int globerMallocVarLen = getGloberMalloc(globeMallocName);

	string temp = "";
	string single[255] = {""};
	int slen = 0;
	for(i=0; i<globerMallocVarLen; i++)
	{
		for(j=0; j<cmdCount; j++)
		{
			temp = command[j];
			slen = covertCmd(temp, single);
			if(isIn("free", single, slen) && isIn(globeMallocName[i], single, slen)) // 释放了
			{
				memLeakFlag = 1; 
				break;
			}
			if(globeMallocName[i] == single[0] && "=" == single[1])
			{
				memLeakFlag = -1;   // 未释放就改变了其值
				break;
			}
		}
		if(-1 == memLeakFlag)  // 存在内存泄漏
		{
			//查找该全局变量的位置
			for(j=0; i<cmdCount; j++)
			{
				temp = command[j];
				slen = covertCmd(temp, single);
				if(isIn(globeMallocName[i], single, slen))
				{
					errNum[errLen] = j+1;
					errType[errLen] = 7;
					errLen++;
					break;
				}
			}
		}
	}
}