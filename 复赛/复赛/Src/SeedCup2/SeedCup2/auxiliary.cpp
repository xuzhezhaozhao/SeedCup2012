//辅助函数

#include"SeedCup2.h"

//功能：判断该行命令(行命令已经经过了字符串的转换了)是不是函数定义(不是声明)的开头，如"void main()"，"static int myFunc()"len是字符串数组的有效长度
//返回值：是返回true
bool isFuncDef(string single[], int len)
{
	if(0 == len)
	{
		return false;
	}
	// 开头数据类型，结尾没有分号就是函数定义了
	else if(isType(single[0]) || "const" == single[0] || "signed" == single[0] || "unsigned" == single[0] || 
			"extern" == single[0] || "static" == single[0] || "void" == single[0])
	{
		if(";" != single[len-1])
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

//功能：判断该行命令(行命令已经经过了字符串的转换了)是不是函数声明(不是定义)，返回值类型不包含const,[un]singed,extern,static，如"void myFunc();", len是字符串数组的有效长度
//返回值：是返回true
bool isFuncState1(string single[], int len)
{
	if(0 == len)
	{
		return false;
	}
	// 开头数据类型，结尾有分号, 分号前是括号，第3个是括号
	else if(isType(single[0]) || "void" == single[0] )
	{
		if(";" == single[len-1] && "(" == single[2] && ")" == single[len-2])
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

//功能：判断该行命令(行命令已经经过了字符串的转换了)是不是函数声明(不是定义)，返回值类型包含const,[un]singed,extern,static，如"extern void myFunc();", len是字符串数组的有效长度
//返回值：是返回true
bool isFuncState(string single[], int slen)
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
		if(isFuncState1(temp, slen-1))
			return true;
	}
	else
	{
		if(isFuncState1(single, slen))
			return true;
	}

	return false;
}

//大括号匹配查询，如果single数组中的左大括号则bracket值加1，有右大括号则bracket值减1
void getBracket(string single[], int len, int & bracket)
{
	int i=0;
	for(i=0; i<len; i++)
	{
		if("{" == single[i])
			bracket++;
		else if("}" == single[i])
			bracket--;
		else
			continue;
	}
}

//小括号匹配查询，如果single数组中的左小括号则bracket值加1，有右小括号则bracket值减1
void getLittleBracket(string single[], int len, int & bracket)
{
	int i=0;
	for(i=0; i<len; i++)
	{
		if("(" == single[i])
			bracket++;
		else if(")" == single[i])
			bracket--;
		else
			continue;
	}
}

//待检字符串是否是数据类型关键字int,float,double,long,short,char
bool isType(string test)
{
	if("int" == test || "float" == test || "double" == test || "long" == test || "char" == test || "short" == test)
		return true;
	else
		return false;
}

//功能： 指定字符串数组中是否存在指定字符串，len为数组长度，pos[]数组保存字符串出现的位置
//返回值：不存在返回－1，存在则返回该字符串出现次数
int isContain(string str,string contain[], int len, int pos[])
{
	int flag = -1;
	int i, j;
	j = 0;
	
	for(i=0; i<len; i++)
	{
		if(str == contain[i])
		{
			flag = 1;
			pos[j] = i;
			j++;
		}
	}
	if(1 == flag)
		return j;
	else
		return flag;
} 

//指定字符串数组中是否存在指定字符串, 不区分大小写，len为数组长度，存在则返回true，不存在返回false
bool isIn(string str,string contain[], int len)
{
	int i;
	for(i=0; i<len; i++)
	{
		if( 0 == _stricmp(str.c_str(), contain[i].c_str()) )
		{
			return true;
		}
	}

	return false;
}

//功能：得到一个字符串在文件出现的次数
//返回值：次数
int getCount(string test)
{
	int i;
	int count = 0; // 字符串出现的次数 
	string temp = ""; // 保存一条命令
	string single[255] = {""};
	int slen = 0;
	int posCount = 0;
	int pos[10] = {-1};
	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		slen = covertCmd(temp, single);
		posCount = isContain(test,single, slen, pos);
		if(-1 != posCount)  // 如果该行中含有该字符串
		{
			count = count + posCount;
		}
	}

	return count;
}


//功能：检测字符串是否是#define命令
//返回值：是返回true
bool checkDef(string test)
{
	string single[255] = {""};
	int slen = 0;
	slen = covertCmd(test, single);

	if("#define" == single[0])
	{
		return true;
	}
	else
	{
		return false;
	}
}

//功能：按两个比较级升序排序，先按one排序，one相同则按two排序
//参数：两个数组长度相同，为len
void sortTwo(int one[], int two[], int len)
{
	int i, j;
	int temp;
	for(i=0; i<len-1; i++)
	{
		for(j=i+1; j<len; j++)
		{
			if(one[i] > one[j])
			{ 
				temp = one[i];
				one[i] = one[j];
				one[j] = temp;

				temp = two[i];
				two[i] = two[j];
				two[j] = temp;
			} 
			else if(one[i] == one[j]) // 相等按two降序排序
			{
				if(two[i] > two[j])
				{
					temp = two[i];
					two[i] = two[j];
					two[j] = temp;
				}
			}
			else
				continue;
		}
	}
}

//功能：检测字符串是否是数字,包含小数，不包含负号的
//返回值：是就返回true
bool onlyNum(string test)
{
	int j;
	int size = test.size();
	if(isNum(test))
	{
		if (checkDot(test))  // 先检测小数点是否只有1个或0个
		{
			for(j=0; j<size; j++)
			{
				if( '.' == test[j] || (test[j] >= '0' && test[j] <= '9'))  // 是数字
				{
					return true;
				}
			}
		}
	}

	return false;
}