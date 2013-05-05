/* 实现5.5.4的功能：未使用的资源之：返回值 */

#include"SeedCup2.h"

//功能：检测每一个函数的调用函数是否用到函数返回值
void uselessReturn()
{
	useReturnOfMalloc(); // 单独检测malloc
	int begin = 0;
	while(-1 != begin)
	{
		begin = uselessReturnFunc(begin);
	}
}

//功能：检测一个函数中的调用函数是否用到函数返回值
//返回值：函数结束下一行减1，没有函数则返回－1
int uselessReturnFunc(int begin)
{
	string func[255] = {""};
	int flen = 0;
	int rowNum = 0;
	rowNum = getFunc(func, begin, flen);
	if(-1 != rowNum)  //找到了函数
	{
		string funcAllName[255] = {""};
		int returnType[255] = {-1};
		int fnlen = getFuncName(funcAllName, returnType);
		int slen = 0;
		string single[255] = {""};
		string haveFuncName = "";
		int reType = -1;
		for(int i=0; i<flen; i++)  // 将函数的每句分别分析
		{
			slen = covertCmd(func[i], single);
			haveFuncName = isHave(funcAllName, fnlen, single, slen);
			if("" != haveFuncName) // 判断该句中有没有函数名
			{
				//有函数名，则判断该函数是否用了返回值
				reType = getFuncType(haveFuncName); // 得到该函数返值类型
				if(1 == reType)  //当其不为void时
				{
					if(haveFuncName == single[0])  //出现返回值无用，没加(void)
					{
						errNum[errLen] = (rowNum-flen+i+1);
						errType[errLen] = 5;
						errLen++;
					}
				}
			}
		}
		return rowNum;
	}
	else
		return -1;
}

//功能：根据函数名得到指定函数返回值类型，0：void 1:其他
//返回值：0，1, -1函数不存在
int getFuncType(string funcName)
{
	int fnlen = 0;  //函数总个数
	string funcAllName[255] = {""};
	int returnType[255] = {-1};

	fnlen = getFuncName(funcAllName, returnType);

	for(int i=0; i<fnlen; i++)
	{
		if(funcName == funcAllName[i])
		{
			return returnType[i];
		}
	}
	return -1;
}

//功能：判断cmp的有没有在std中的元素
//参数：len1 std长度，len2 cmp长度
//返回值：cmp中在std中最先出现的字符串,没有的话返回空字符串
string isHave(string std[], int len1, string cmp[], int len2)
{
	int i, j;

	for(i=0; i<len2; i++)
	{
		for(j=0; j<len1; j++)
		{
			if(cmp[i] == std[j])
			{
				return cmp[i];
			}
		}
	}
	return "";
}


//功能：判断出现malloc函数的地方是否利用了其返回值
void useReturnOfMalloc()
{
	string temp = "";
	string single[255] = {""};
	int slen = 0;
	for(int i=0; i<cmdCount; i++)
	{
		temp = command[i];
		slen = covertCmd(temp,single);
		if(isIn("malloc", single, slen))  //含有malloc没有＝和void的情况就是未使用返回值
		{
			if(!isIn("=", single, slen))
			{
				if(!isIn("void", single, slen))
				{
					errNum[errLen] = i+1;
					errType[errLen] = 5;
					errLen++;
				}
			}
		}
	}
}