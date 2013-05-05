/* 实现5.6的功能: 函数关系调用图(简单及递归) */

#include"SeedCup2.h"

/*
功能：根据第三步得出的二维图按要求的格式打印出函数调用图
*/
void getGraphic(string step[][100])
{

	int i, j;
	int tempLen = 0;  // 每一行中的有效字符串数
	int mainLen = graphStep3(step);
	for(i=0; i<mainLen; i++)
	{
		tempLen = getMainEdgeNum(i, step)+1;
		for(j=0; j<tempLen; j++) // 最后为"*"的要考虑，不打印，而且最后一个函数不需要补'-'了
		{
			if("*" == step[i][j+1])
			{
				cout << step[i][j];
				break;
			}
			else if(tempLen-1 == j)
			{
				cout << step[i][j];
			}
			else
			{
				covertStep(step[i][j]);
				cout << step[i][j];
			}
		}	
		cout << endl;
	}
}

/*
功能：第一步，仅仅先得到指定单个函数(不包含main函数)的调用关系, 如下形式, 表示f1调用f2和f3, 结果保存在一个二维数组step1[][100](有多少调用函数就有多少行)中
f1 f2
#  f3
返回值：二维数组行数，即调用函数个数
*/
int graphStep1(string funcName, string step1[][100])
{
	int i;
	string tempInFuncName[255] = {""}; // 调用的函数名, 有重名
	int tempInLen = getFuncName(tempInFuncName, funcName);

	string inFuncName[255] = {""};
	int inLen = delRepeat(tempInFuncName, tempInLen, inFuncName); // 删除重名函数
	sortStringIncr(inFuncName, inLen);   //升序排列

	for(i=0; i<inLen; i++)
	{
		if(0 == i)
		{
			step1[i][0] = funcName;
		}
		else
		{
			step1[i][0] = "#";
		}
		step1[i][1] = inFuncName[i];
	}
	return inLen;
}

/*
功能：第二步，得到main函数的调用关系, 但main函数的维数应该更大，定义为100*100的，必须初始化为空
返回值：二维数组行数，即调用函数个数
*/
int graphStep2(string funcName, string step2[][100])
{
	int i;
	string tempInFuncName[255] = {""}; // 调用的函数名, 有重名
	int tempInLen = getFuncName(tempInFuncName, funcName);

	string inFuncName[255] = {""};
	int inLen = delRepeat(tempInFuncName, tempInLen, inFuncName); // 删除重名函数
	sortStringIncr(inFuncName, inLen);   //升序排列

	for(i=0; i<inLen; i++)
	{
		if(0 == i)
		{
			step2[i][0] = funcName;
		}
		else
		{
			step2[i][0] = "#";
		}
		step2[i][1] = inFuncName[i];
	}
	return inLen;
}

/*
功能：第三步, 迭代，产生完整的二维函数调用图，其中"#"代表10个"-","*"表示空，标志递归的结束
返回值：二维图的行数
*/
int graphStep3(string step3[][100])
{
	int i;
	int mainLen = graphStep2("main", step3);   //绘制主函数的调用情况
	for(i=0; i<mainLen; i++)
	{
		if(isInvokeFunc(getMainEdge(i, step3)))
		{
			mainLen = insertNewFunc(step3, mainLen, i);
			isRecursive(step3, i);
			i--;  //i减1去判断新这一行增加的一个函数有没有调用其他函数
		}
	}

	return mainLen;
}


//功能：得到指定函数调用的函数名，不检查重名，结果保存在funcName数组中
//返回值：数组长度
int getFuncName(string funcName[], string thisFuncName)
{
	string func[255] = {""};
	int flen = 0;
	getFuncFromName(func, flen, thisFuncName);   // 将该函数读出

	string single[255] = {""};
	int slen = 0;	
	
	int fnlen = 0; //调用函数个数
	for(int i=1; i<flen; i++)   //函数声明的这一行先排除掉
	{
		getFuncNameFromCmd(func[i], funcName, fnlen);
	}
	return fnlen;
}

//功能：得到一条语句中的函数名, 结果追加存在funcNameFromCmd[]中, len是数组之前的长度
void getFuncNameFromCmd(string cmd, string funcNameFromCmd[], int & len)
{
	int slen = 0;
	string single[255] = {""};
	slen = covertCmd(cmd, single);
	string allFuncName[255] = {""};
	int tempType[255] = {0};

	int fnlen = getFuncName(allFuncName, tempType);  // 得到全部函数名数组
	haveGet(allFuncName, fnlen, single, slen, funcNameFromCmd, len);  //将命令中的函数名追加存在funcNameFromCmd[]中
}

//功能：去除字符串数组中重复的字符串,结果存放在clean[]中
//参数：len，test[]长度
//返回：clean长度
int delRepeat(string test[], int len, string clean[])
{
	int i;
	int clen = 0;
	for(i=0; i<len; i++)
	{
		if(!isIn(test[i], clean, clen))
		{
			clean[clen] = test[i];
			clen++;
		}
	}
	return clen;
}

//功能：对指定的string数组升排序，长度为len
void sortStringIncr(string str[], int len)
{
	int i, j;
	string temp;
	for(i=0; i<len-1; i++)
	{
		for(j=i+1; j<len; j++)
		{
			if(str[i] > str[j])
			{
				temp = str[i];
				str[i] = str[j];
				str[j] = temp;
			}
		}
	}
}

//功能：判断指定函数是否调用了其他函数
//返回值：调用了返回true, 没有调用返回false
bool isInvokeFunc(string funcName)
{
	string step1[20][100] = {""};
	int len = graphStep1(funcName, step1);
	if(0 == len)  // 没有调用
	{
		return false;
	}
	else
		return true;

}

//功能：得到main函数二维调图第row行（0起始）未尾元素的值
//返回值：未尾字符串
string getMainEdge(int row, string step[][100])
{
	int edge = 0;
	while("" != step[row][edge])
	{
		edge++;
	}

	if(0 != edge)
		return step[row][edge-1];
	else
		return "";
}

//功能：得到main函数二维调图第row行（0起始）未尾元素的列号（0起始）
//返回值：未尾列号
int getMainEdgeNum(int row, string step[][100])
{
	int edge = 0;
	while("" != step[row][edge])
	{
		edge++;
	}
	return (edge-1);
}

//功能：在main二维图未端插入新的拓补结构
//返回值：二维图的有效行数
int insertNewFunc(string step[][100], int stepLen, int row)
{
	int i, j;
	int tempNum = 0;
	string funcEdge = getMainEdge(row, step);  // 得到未端函数名，OK
	string step1[20][100] = {""};
	int funcEdgeLen = graphStep1(funcEdge, step1);  //得到调用函数的调用关系和其行数

	/* row行后的下移funcEdgeLen－1行 */
	for(i=stepLen-1; i>row; i--)
	{
			for(j=0; j<100; j++)
			{
				step[i+funcEdgeLen-1][j] = step[i][j];
			}
	}

	/* 在原先下移的行位置填 "#" */
	tempNum = getMainEdgeNum(row, step)+1;
	for(i=row+1; i<row+funcEdgeLen; i++)
	{
		for(j=0; j<tempNum; j++)
		{
			step[i][j] = "#";
		}
	}

	tempNum = getMainEdgeNum(row, step);
	j = 0;
	for(i=row; i<(row+funcEdgeLen); i++)
	{
		step[i][tempNum+1] = step1[j][1];
		j++;
	}

	return (stepLen+funcEdgeLen-1);
}


//功能：判断在row行是否产生了递归, 思想就是判断在该维上最后一个字符串是否和前面的相同，相同就是递归，
//+产生递归后将最后一个字符串的后一个字符串置为 "*",可以结束递归
void isRecursive(string step[][100], int row)
{
	int len = getMainEdgeNum(row, step)+1;  //得到该维上的字符串个数
	for(int i=0; i<len-1; i++)
	{
		if(step[row][len-1] == step[row][i])  //出现递归
		{
			step[row][len] = "*"; // 将最后一个置为"*"
		}
	}
}


//功能：按要求转换二维图中的字符串，"#"变成10个"-", 函数名补齐，"*"转成空
void covertStep(string & str)
{
	int i;
	if("#" == str)
		str = "----------";
	else if("*" == str)
		str = "";
	else 
	{
		if("" != str)
		{
			int size = str.size();
			for(i=size; i<10; i++)
			{
				str = str + "-";
			}
		}
	}
}