#include"SeedCup2.h"


// 功能：将与一个函数定义有关的命令行从command[]中取出，存入到func数组中，
//+ 从command[]的begin位置(0起始)开始查找函数，只读入找到的第一个函数，包括main函数
//+ 如 void func(){int i=1;
//+			int j=8;
//+		}  
//+ 将其按行存入func[]中,存入的是原始命令，没有经过处理
//返回值：返回读取的函数下一行行号减1的值,若之后没有找到函数则返回－1
//参数：begin查找起始位置，func_len是该函数的总行数
int getFunc(string func[], int begin, int & func_len)
{
	int i=0;
	int j=0;
	int k=0;
	func_len = 0;
	string single[100] = {""};
	string temp = "";
	int len = 0;
	int bracket = 0;  // 大括号匹配检测

	for(i=begin; i<cmdCount; i++)
	{
		temp = command[i];
		len = covertCmd(temp, single);

		if(isFuncDef(single, len)) // 判断是否是函数定义的开始
		{
			// 是函数的开始，操作完成后就要break出循环
			bracket = 0;  //大括号匹配值初始为0
			j = 0;
			for(k=i; k<cmdCount; k++)
			{
				func[j] = command[k];   // 先将该行赋给func[j]
				func_len = j+1;
				j++;
				temp = command[k];
				len = covertCmd(temp, single);

				if(k == i && "}" == single[len-1])
				{
					return (k+1);
				}
				else
				{
					getBracket(single, len, bracket); // 得到大括号匹配情况

					if(k!=i && 0 == bracket)   // 大括号匹配完成，说明函数定义结束
					{
						return (k+1);
					}
					else // 没有匹配结束，说明函数定义还没有结束
					{
						continue;
					}
				}
			}
		}
	}

	return -1;
}


//功能：读取指定函数名的函数
void getFuncFromName(string func[], int & func_len, string funcName)
{
	int funcPos = getFuncPosFromName(funcName);
	if(-1 != funcPos)
	{
		(void)getFunc(func, funcPos, func_len);
	}
}

// 功能：将#define定义的宏名依次存到def数组中,如#define MAX 100, 将MAX存入def
// 返回：返回宏个数
int getDefine(string def[])
{
	int i=0;

	string temp = "";
	string single[255] = {""};
	int len = 0;

	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		single[0] = "";
		covertCmd(temp, single);
		
		if("#define" == single[0])
		{
			def[len] = single[1];
			len++;
		}
	}
	return len;
}

//功能：得到函数中的变量名，包括形参名
//参数：参数：begin查找起始位置，只查找找到的第一个函数
//返回值：变量个数
int getFuncVar(string funcVar[], int begin)
{
	int len = 0;  //变量数组长度
	int flen = 0; // 函数总的行数
	int i;
	string func[255] = {""};
	getFunc(func, begin, flen);
	for(i=0; i<flen; i++)
	{
		getVar(func[i], funcVar, len);
	}
	return len;
}

//功能：将一条变量声明语句(不含有const,sttic,signed,unsigned,extern开头)中的变量名赋给funVar[len]，len是原有的数组长度，这样可以保存原来的变量,
//+不能得到声明函数的形参名， 如int const**i, j, k, m;
void getVar1(string single[], int slen, string funcVar[], int & len)
{
	int i=0;
	if(isType(single[0]))
	{
		//得到声明变量名 int i;  int *p; int **p; int & s; 加const
		if("(" != single[2])   
		{
			if("*" != single[1] && "**" != single[1] && "&" != single[1])  // int i;int const i;int const* i;
			{
				if("const" != single[1]) // int i;
				{
					funcVar[len] = single[1];
					len++;
			
					for(i=2; i<slen; i++) // 检查int i=0, j;这种情况
					{
						if("," == single[i])
						{
							funcVar[len] = single[i+1];
							len++;
						}
					}
				}  
				else if ("const" == single[1] && "*" != single[2] && "**" != single[2])
				{
					funcVar[len] = single[2];
					len++;
			
					for(i=3; i<slen; i++) // 检查int const i=0, j;这种情况
					{
						if("," == single[i])
						{
							funcVar[len] = single[i+1];
							len++;
						}
					}
				}  // int const* i;int const ** i;
				else if("const" == single[1] && ("*" == single[2] || "**" == single[2]) )
				{
					funcVar[len] = single[3];
					len++;
			
					for(i=4; i<slen; i++) // 检查int const i=0, j;这种情况
					{
						if("," == single[i])
						{
							funcVar[len] = single[i+1];
							len++;
						}
					}
				}		
				else
				{
					;
				}
			}
			else   //int * i; int *const i; int & i;
			{
				if("const" != single[2])  // int * i; int & i;
				{
					funcVar[len] = single[2];
					len++;
					for(i=3; i<slen; i++) // 检查int* i=0, j;这种情况
					{
						if("," == single[i])
						{
							funcVar[len] = single[i+1];
							len++;
						}
					}
				}
				else
				{
					funcVar[len] = single[3];
					len++;
					for(i=4; i<slen; i++) // 检查int* const i=0, j; int const *i, j;这种情况
					{
						if("," == single[i])
						{
							funcVar[len] = single[i+1];
							len++;
						}
					}
				}
			}
		}
	}
	funcVar[len] = "";
}

//功能：类似getVar1,不过增加了识别signed 和 unsigned
void getVar2(string single[], int slen, string funcVar[], int & len)
{
	int i, j;
	string temp[255] = {""};
	if("signed" == single[0] || "unsigned" == single[0])
	{
		j = 0;
		for(i=1; i<slen; i++)
		{
			temp[j] = single[i];
			j++;
		}	
		getVar1(temp, slen-1, funcVar, len);
	}
	else
	{
		getVar1(single, slen, funcVar, len);
	}
}

//功能：类似getVar2,不过在其基础上增加了识别const开头的
void getVar3(string single[], int slen, string funcVar[], int & len)
{
	int i, j;
	string temp[255] = {""};
	if("const" == single[0])
	{
		j = 0;
		for(i=1; i<slen; i++)
		{
			temp[j] = single[i];
			j++;
		}
		getVar2(temp, slen-1, funcVar, len);
	}
	else
	{
		getVar2(single, slen, funcVar, len);
	}
}

//功能：类似getVar3,不过在其基础上增加了识别extern或static开头的
void getVar4(string single[], int slen, string funcVar[], int & len)
{
	int i, j;
	string temp[255] = {""};
	if("extern" == single[0] || "static" == single[0])
	{
		j = 0;
		for(i=1; i<slen; i++)
		{
			temp[j] = single[i];
			j++;
		}
		getVar3(temp, slen-1, funcVar, len);
	}
	else
	{
		getVar3(single, slen, funcVar, len);
	}
}

//功能：与getVar2()功能类似，不过在其基础上增加了识别声明函数的形参名，但返回值类型不包含const,[un]singed,extern,static，如 void func(signed int const* p1, float *const p2)
void getVar5(string single[], int slen, string funcVar[], int & len)
{
	string temp[20][255] = {""};
	int tlen[20] = {0};
	int i, j, k;

	i = 0;
	j = 0;
	k = 0;
	if(isFuncDef(single, slen))
	{			
		if("void" != single[3]) // void func(void)
		{
			for(i=3; i<slen; i++)
			{
				k=0;
				while("," != single[i] && (slen-1) != i)
				{
					temp[j][k] = single[i];
					tlen[j]++;
					k++;
					i++;
				}
				j++;
			}
		}

		for(i=0; i<j; i++)
		{
			getVar4(temp[i], tlen[i], funcVar, len);
		}
	}
}

//功能：与getVar5()功能类似，不过在其基础上增加了返回值类型包含const,[un]singed,extern,static，如 static void func(signed int const* p1, float *const p2)
void getVar6(string single[], int slen, string funcVar[], int & len)
{
	int i, j;
	string temp[255] = {""};
	if("extern" == single[0] || "static" == single[0] || "singed" == single[0] || "unsigned" == single[0] || 
		"const" == single[0] )
	{
		j = 0;
		for(i=1; i<slen; i++)
		{
			temp[j] = single[i];
			j++;
		}
		getVar5(temp, slen-1, funcVar, len);
	}
	else
	{
		getVar5(single, slen, funcVar, len);
	}
}

//功能：综合getVar，解析出一条命令中定义的参数名
void getVar(string cmd, string funcVar[], int & len)
{
	string single[255] = {""};

	int slen;
	slen = covertCmd(cmd, single);

	getVar4(single, slen, funcVar, len);
	getVar6(single, slen, funcVar, len);
}

//功能：得到全局变量名
//返回值：全局变量数组长度
int getGlobeVar(string globeVar[])
{
	int i=0;
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
			getVar(temp, globeVar, glen);
		}
		else
		{
			break;
		}
	}
	return glen;
}


//功能：得到全部的函数名及对应的返回值类型，0表示void,1表示其他，包括main函数
//返回值：数组长度
int getFuncName(string funcName[], int returnType[])
{
	string single[255] = {""};
	int slen = 0;
	string temp = "";
	int nlen = 0;
	for(int i=0; i<cmdCount; i++)
	{
		temp = command[i];
		slen = covertCmd(temp, single);
		if(isFuncDef(single, slen))   // 如果是函数定义，只有定义了的函数才能被调用
		{
			funcName[nlen] =  getFuncStaName(single, slen, returnType[nlen]);
			nlen++;
		}
	}

	//添加指定的系统函数
	funcName[nlen] = "malloc";
	returnType[nlen] = 0;   // !!! 注意：本来malloc的值应该为1，但因为"（*int）malloc();"会产生误判,所以写一单独一个函数检测malloc返回值
 	nlen++;
	funcName[nlen] = "free";
	returnType[nlen] = 0;
	nlen++;
	funcName[nlen] = "getchar";
	returnType[nlen] = 1;
	nlen++;

	return nlen;
}

//功能：得到函数定义语句中函数名及返回值类型
string getFuncStaName(string single[], int slen, int & returnType)
{
	returnType = 1;
	int i=0;
	while("(" != single[i])
	{
		if("void" == single[i])
		{
			returnType = 0;
		}
		i++;
	}

	return single[i-1];
}


//功能：得到指定函数定义的位置(0起始)
//返回值：位置，不存在返回－1
int getFuncPosFromName(string funcName)
{
	int i = 0;
	string temp = "";
	string single[255] = {""};
	int slen = 0;
	int tempType = 0;
	string tempName = "";
	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		slen = covertCmd(temp, single);
		if(isFuncDef(single, slen))
		{
			tempName = getFuncStaName(single, slen, tempType);
			if(tempName == funcName)
			{
				return i;
			}
		}
	}
	return -1;
}

//功能：判断cmp的有没有在std中的元素，有的话追加存在get数组中
//参数：len1 std长度，len2 cmp长度, len3 get长度
void haveGet(string std[], int len1, string cmp[], int len2, string get[], int & len3)
{
	int i, j;

	for(i=0; i<len2; i++)
	{
		for(j=0; j<len1; j++)
		{
			if(cmp[i] == std[j])
			{
				get[len3] = cmp[i];
				len3++;
			}
		}
	}
}