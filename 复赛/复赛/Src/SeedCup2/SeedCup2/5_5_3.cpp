/* 实现5.5.3的功能：未使用的资源之：变量 */

#include"SeedCup2.h"

//功能：检测未使用的变量，包括局部、全局变量
void uselessVar()
{
	uselessGlobeVar();
	uselessAllFuncVar();
}

//功能：检测全局变量是否使用
void uselessGlobeVar()
{
	string globeVar[100] = {""};
	int begin = 0;
	int glen = 0;
	int gPos = 0; // 全局变量的位置
	glen = getGlobeVar(globeVar);
	int gflag = -1;
	for(int i=0; i<glen; i++)
	{
		begin = 0;
		while(-1 != begin)
		{
			begin = isGlobeInFunc(globeVar[i], begin, gflag);
			if(1 == gflag)
			{
				break;
			}
		}
		if(-1 == gflag)   // 在每个函数中没有用到
		{
			gPos = getGolbeVarPos(command, cmdCount, globeVar[i]);
			errNum[errLen] = gPos+1;
			errType[errLen] = 5;
			errLen++;
		}
	}
}

//功能：检测全局变量在函数中里否使用，还要考虑局部变量的影响
//参数：gfag初始为－1，如果变为了1,说明使用到了该全局变量
//返回值：函数结束行下一行减1，找不到函数则返回－1,
int isGlobeInFunc(string globeVar, int begin, int & gflag)
{
	gflag = -1;
	string func[255] = {""};
	int flen = 0;
	int rowNum = 0;
	rowNum = getFunc(func, begin,  flen);
	if(-1 != rowNum)
	{
		string funcVar[100] = {""};
		int vlen = 0;
		vlen = getFuncVar(funcVar, begin);
		if(!isIn(globeVar, funcVar, vlen))  // 局部变量没有覆盖的情况
		{
			if(!isUselessGlobeVar(func, flen, globeVar))  // 如果用到了globeVar,考虑了"globeVar;"这种情况, 就把gflag置为1
			{
				gflag = 1;
			}
		}

		return rowNum;
	}
	else
		return -1;
}

//功能：检测所有函数中未使用的变量
void uselessAllFuncVar()
{
	int begin = 0;
	while(-1 != begin)
	{
		begin = uselessFuncVar(begin);
	}
}


//功能：检测一个函数中未使用的变量
//参数：函数查找的起始位置
//返回值：函数结束的下一行减1
int uselessFuncVar(int begin)
{
	string func[255] = {""};
	int flen = 0;
	int rowNum = 0;
	string funcVar[255] = {""};
	int vlen = 0;
	rowNum = getFunc(func, begin, flen);
	if(-1 != rowNum)
	{
		vlen = getFuncVar(funcVar, begin);
		int varPos = 0;

		for(int i=0; i<vlen; i++)
		{
			if(isUselessFuncVar(func, flen, funcVar[i])) // 如果是无用变量
			{
				varPos = getFirstAppearPos(func, flen, funcVar[i]);
				errNum[errLen] = rowNum-flen+varPos+1; 
				errType[errLen] = 5;
				errLen++;
			}
		}
		return rowNum;
	}
	else
		return -1;
}

/*
功能：检测一个变量在函数是否用过, 如"int i; i;" 这样的不算用过
1.自己被改写
2.给其它变量赋值
3.间接决定其它变量数值. eg b = p[a]中的a
思想就是检测变量出现的次数
返回值：无用返回true, 有用则返回false
*/
bool isUselessFuncVar(string func[], int flen, string varName)
{
	int i;
	int count = 0; // 字符串出现的次数 
	string temp = ""; // 保存一条命令
	string single[255] = {""};
	int slen = 0;
	int posCount = 0;
	int pos[10] = {-1};
	for(i=0; i<flen; i++)
	{
		temp = func[i];
		slen = covertCmd(temp, single);
		if(varName == single[0] && ";" == single[1])  // 先排除 "i;"这种情况
		{
			continue;
		}
		posCount = isContain(varName,single, slen, pos);
		if(-1 != posCount)  // 如果该行中含有该字符串
		{
			if((isIn("=", single, slen) || isIn("--", single, slen) || isIn("++", single, slen) || isIn("return", single, slen))
				|| (isIn("int", single, slen) || isIn("float", single, slen) || isIn("char", single, slen) || isIn("double", single, slen) || isIn("long", single, slen)
				|| isIn("short", single, slen) || isIn("signed", single, slen) || isIn("unsigned", single, slen))) // 含有变量，而且有"= ++ --"字符，或者是变量声明语句
			{
				count = count + posCount;
			}
		}
	}

	if(count > 1)
	{
		return false;
	}
	else
		return true;
}

/*
功能：检测一个全局变量在函数是否用过
1.自己被改写
2.给其它变量赋值
3.间接决定其它变量数值. eg b = p[a]中的a
返回值：无用返回true, 有用则返回false
*/bool isUselessGlobeVar(string func[], int flen, string varName)
{
	int i;
	int count = 0; // 字符串出现的次数 
	string temp = ""; // 保存一条命令
	string single[255] = {""};
	int slen = 0;
	int posCount = 0;
	int pos[10] = {-1};
	for(i=0; i<flen; i++)
	{
		temp = func[i];
		slen = covertCmd(temp, single);
		if(varName == single[0] && (";" == single[1]))  // 先排除 "i;"
		{
			continue;
		}
		posCount = isContain(varName,single, slen, pos);
		if(-1 != posCount)  // 如果该行中含有该字符串
		{
			if((isIn("=", single, slen) || isIn("--", single, slen) || isIn("++", single, slen) || isIn("return", single, slen))
				|| (isIn("int", single, slen) || isIn("float", single, slen) || isIn("char", single, slen) || isIn("double", single, slen) || isIn("long", single, slen)
				|| isIn("short", single, slen) || isIn("signed", single, slen) || isIn("unsigned", single, slen))) // 含有变量，而且有"= ++ --"字符，或者是变量声明语句
			{
				count = count + posCount;
			}
		}
	}

	if(count > 0)
	{
		return false;
	}
	else
		return true;
}

//功能：得到变量名在函数中第一次出现的位置
//返回值：位置（0起始）,不存在返回－1
int getFirstAppearPos(string func[], int flen, string varName)
{
	int i, j;
	string temp = "";
	int slen = 0;
	string single[255] = {""};
	
	for(i=0; i<flen; i++)
	{
		temp = func[i];
		slen = covertCmd(temp, single);
		for(j=0; j<slen; j++)
		{
			if(varName == single[j])
			{
				return i;
			}
		}
	}

	return -1;
} 

//功能：得到全局变量名第一次出现的位置
//返回值：位置（0起始）,不存在返回－1
int getGolbeVarPos(string cmd[], int len, string varName)
{
	int i, j;
	string temp = "";
	int slen = 0;
	string single[255] = {""};
	
	for(i=0; i<len; i++)
	{
		temp = cmd[i];
		slen = covertCmd(temp, single);
		for(j=0; j<slen; j++)
		{
			if(varName == single[j])
			{
				return i;
			}
		}
	}

	return -1;
} 