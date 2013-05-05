/* 实现5.5.1的功能：未使用的资源之：函数  */

#include"SeedCup2.h"

//功能：处理未使用的函数
void uselessFunc()
{
	uselessFunc1();
	uselessFunc2();
}

//功能：处理未使用的函数资源之：当该函数有声明的情况
void uselessFunc1()
{
	int i;
	int begin = 0;
	string single[255] = {""};
	string temp = "";
	int slen = 0;
	string funcName = "";
	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		slen = covertCmd(temp, single);
		if(isFuncState(single, slen))    // 如果是函数声明时进行处理
		{
			funcName = getFuncName(single, slen);
			if(getCount(funcName) < 3)  // 如果是无用函数
			{
				errNum[errLen] = i+1;
				errType[errLen] = 5;
				errLen++;
			//	cout << "line=" << errNum[errLen-1] << ",error=5" << endl; // for debug
			}
		}
	}
}

//功能：处理未使用的函数资源之：当该函数无声明，只有定义的情况
void uselessFunc2()
{
	int i;
	int begin = 0;
	string single[255] = {""};
	string temp = "";
	int slen = 0;
	string funcName = "";
	string StaFuncName[255] = {""};  // 有函数声明的函数名
	int sflen = 0;
	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		slen = covertCmd(temp, single);
		if(isFuncDef(single, slen))    // 如果是函数定义时进行处理
		{
			sflen = getStaFuncName(StaFuncName);
			funcName = getFuncName(single, slen);
			if(!isIn(funcName, StaFuncName, sflen)) // 如果函数没有声明
			{
				if(getCount(funcName) < 2 && "main" != funcName)  // 如果是无用函数
				{
					errNum[errLen] = i+1;
					errType[errLen] = 5;
					errLen++;
				//	cout << "line=" << errNum[errLen-1] << ",error=5" << endl; // for debug
				}
			}
		}
	}
}


//功能：得到函数声明或定义命令中的函数名
//返回值：得到的函数名
string getFuncName(string single[], int slen)
{
	int i = 0;
	string funcName = "";
	while("(" != single[i])
	{
		i++;
	}

	funcName = single[i-1];

	return funcName;
}

//功能：将有声明的函数的名保存在数组StaFuncName中
//返回值：数组长度
int getStaFuncName(string StaFuncName[])
{
	int i=0;
	int nlen = 0;
	string temp = "";
	string single[255] = {""};
	int slen = 0;
	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		slen = covertCmd(temp, single);
		if(isFuncState(single, slen)) // 如果是函数声明
		{
			StaFuncName[nlen] = getFuncName(single, slen);
			nlen++;
		}
	}

	return nlen;
}
