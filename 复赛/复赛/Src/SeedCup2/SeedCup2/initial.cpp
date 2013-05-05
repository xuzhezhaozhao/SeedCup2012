#include"SeedCup2.h"

//功能：读取命令到全局变量，并将注释置为空
void initial(string inputFile)
{
	 readFile(inputFile);   // 读取文本中的命令
	 delAnnotation();   // 删除注释
	 delCmdString();		//删除命令中双引号之间的内容
}

//功能：读取指定文件的每行到全局变量command[]中保存，空行也算，cmdCount中保存读入命令的条数
void readFile(string inputFile)
{	
	cmdCount = 0;
	char temp[255] = "";  // 存放一行命令

	ifstream fin(inputFile, ifstream::in);   // 打开文件
	while(!fin.eof())
	{
		fin.getline(temp,254,'\n');   // 读入一行命令到temp，以换行符分隔
		command[cmdCount] = temp;
		cmdCount++;
	}

	fin.close();   // 关闭文件
}

//功能：删除注释, 可以删除行间注释，将注释置为空
void delAnnotation()
{
	int i, j, k;
	int pose_begin, pose_end;
	for(i = 0; i<cmdCount; i++)
	{
		pose_begin = command[i].find("/*");
		if(pose_begin != -1)
		{
			for( j=i; j<cmdCount; j++)
			{
				pose_end = command[j].find("*/");
				if(pose_end != -1)
				{
					for( k = i+1; k < j; k++)
					{
						command[k] = "";
					}
					if(i == j)
					{
						command[i] = command[i].substr(0, pose_begin)
							+command[i].substr(pose_end + 2, command[i].size() - pose_end -2);
					}
					else
					{
						command[i] = command[i].substr(0, pose_begin);
						command[j] = command[j].substr(pose_end + 2,command[j].size() - pose_end -2);
					}
					break;
				}
			}
		}
	}
}

//功能：宏替换, 包含带参数和不带参数的情况
void macroReplace()
{
	macroSimpleReplace();
	macroComplexReplace();
}

//功能：不带参数的宏替换，#define MAX (100*100)
void macroSimpleReplace()
{
	int i, j, k;
	string macroName = "";
	string macroValue = "";

	int pos[10] = {-1};
	int posCount = -1;

	string temp = "";
	string single[255] = {""};
	int slen = 0;
	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		slen = getSingle(temp, single);
		if("#define" == single[0] && 3 == slen) // 形如 #define MAX (100*100)
		{
			macroName = single[1];
			macroValue = single[2];

			for(j=i+1; j<cmdCount; j++)
			{
				temp = command[j];
				slen = covertCmd(temp, single);
				posCount = isContain(macroName, single, slen, pos);
				if(-1 != posCount) // 说明含有宏，要替换
				{
					for(k=0; k<posCount; k++)
					{
						single[pos[k]] = " " + macroValue + " ";
					}
					command[j] = "";
					//将替换后的字符串拼回命令行中
					for(k=0; k<slen; k++)
					{
						single[k] = " " + single[k] + " ";
						command[j] = command[j] + single[k];
					}
				}
			}
		}
	}
}

//功能：带参数的宏替换
void macroComplexReplace()
{
	int i, j;
	string macroName = "";
	string macroValue = "";

	int pos[10] = {-1};
	int posCount = -1;

	string temp = "";
	string single[255] = {""};
	int slen = 0;
	string macroDef = "";
	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		if(isComplexMacroDef(temp))  // 带参宏定义
		{
			macroDef = command[i];
			slen = covertCmd(temp, single);
			macroName = single[1];  // 得到带参数的宏名
			for(j=i+1; j<cmdCount; j++)
			{
				temp = command[j];
				slen = covertCmd(temp, single);;
				if(isIn(macroName, single, slen))   // 调用到了该宏
				{
					command[j] = singleComplexMacroReplace(macroDef, command[j]);
					j--; // 替换一个宏后，再检测一下该行
				}
			}
		}
	}
}

//功能：得到带参数的宏的参数名，将其保存在macroVarName数组中
//参数：macro 宏定义语句
//返回值：参数个数
int getMacroVarName(string macro, string macroVarName[])
{
	int i;
	int macroVarLen = 0;
	string single[255] = {""};
	int slen = 0;
	slen = covertCmd(macro, single);

	for(i=3; i<slen; i++)
	{
		if(")" != single[i])   // 说明没有到参数结束的位置
		{
			if("," != single[i])   // 宏括号内不是逗号就是参数名
			{
				macroVarName[macroVarLen] = single[i]; // 将参数名放在数组中
				macroVarLen++;
			}
		}
		else
		{
			break;
		}
	}

	return macroVarLen;
}

//功能：判断一条语句是否是带参数的宏定义语句
//返回值：是返回true
bool isComplexMacroDef(string test)
{
	string single[255] = {""};
	int slen = 0;
	string tempSingle[255] = {""};
	int templen = 0;
	slen = getSingle(test, single);

	if("#define" == single[0]) // 形如 #define MAX(a, b) ((a)*(b))
	{
		templen = covertCmd(single[1], tempSingle);  // 将带参的宏打散
		if(isIn("(", tempSingle, templen))   // 存左括号，说明这是一个带参的宏的定义
		{
			return true;
		}
	}
	return false;
}

//功能：如#define MAX(a, b) ((a)*(b))  得到((a)*(b)) 打散后的字符串数组
//参数：macro 宏定义语句
//返回值：数组长度
int getComplexMacroValue(string macro, string complexMacroValue[])
{
	int complexMacroValueLen = 0;
	string single[255] = {""};
	int slen = 0;
	slen = covertCmd(macro, single);
	for(int i=0; i<slen; i++)
	{
		if(")" == single[i])   // i之后的就宏值
		{
			for(int j=i+1; j<slen; j++)
			{
				complexMacroValue[complexMacroValueLen] = single[j];
				complexMacroValueLen++;
			}
			break;
		}
	}
	return complexMacroValueLen;
}


//功能：得到使用带参的宏中的传递的值，如MAX(2, (3)) 中的2，(3)，只得到第一个该句中检测到的宏
//参数：macroName 宏名， useMacro 调用该宏的语句，macroVarLen 宏参个数
//返回值：返回将调用的宏打散后的字符串数组的长度
int getComplexMacroRealValue(string macroName, string useMacro, int macroVarLen, string macroRealValue[])
{
	string useSingle[255] = {""};  // 调用宏的语句
	int useLen = 0;

	useLen = covertCmd(useMacro, useSingle);   // 将调用宏语句打散

	int posCount = -1;  // 该语句中调用该宏的次数
	int pos[10] = {-1};   // 调用的位置

	posCount = isContain(macroName, useSingle, useLen, pos);  // 得到调用宏的位置

	int realValueLen = 0;  //传递参数数组长度
	int j;

	//以下是找到宏的右括号出现的位置
	int littleBracket = 0; // 宏的小括号匹配标志
	int rightMacro = 0; // 保存找到的位置

	for(int i=pos[0]+1; i<useLen; i++) // 从宏的左括号位置开始匹配
	{                      
		if("(" == useSingle[i])
		{
			littleBracket++;
		}
		if(")" == useSingle[i])
		{
			littleBracket--;
		}
		if(0 == littleBracket && i != pos[0]+1)
		{
			rightMacro = i;
		}
	}

	//开始提取传递的参数 MAX(a, (b))
	for(int i=pos[0]+2; i<useLen; i++)
	{
		j = i;
		if(0 != macroVarLen)  // 如果有形参
		{
			while("," != useSingle[j] && j != rightMacro) // 不为逗号说明还是一个传递参数, 没有到宏的右括号说明还要查找
			{
				if(j != rightMacro)  // 没有到宏结尾// if(MAX(2, 3))
				{
					macroRealValue[realValueLen] = macroRealValue[realValueLen] + useSingle[j];	
					j++;
				}
				else
				{
					break;   //到宏结尾则跳出
				}
			}
			realValueLen++;
			
			if(j == rightMacro)  // 到了宏的右括号位置
				break;

			i=j;   // i偏移到逗号位置
		}
	}
	int temp = rightMacro-pos[0]+1;
	return temp;
}


//功能：展开单条调用了带参数的宏的语句, 只展开第一个该句中检测到的宏
//参数：macroDef 宏定义语句， useMacro 调用语句，
//返回值：返回展开后的语句
string singleComplexMacroReplace(string macroDef, string useMacro)
{
	int i, j;
	// 得到宏参数名
	int macroVarNameLen = 0;
	string macroVarName[255] = {""};
	macroVarNameLen = getMacroVarName(macroDef, macroVarName); 


	// 如#define MAX(a, b) ((a)*(b))  得到((a)*(b)) 打散后的字符串数组
	int macroValueLen = 0;
	string complexMacroValue[255] = {""};
	macroValueLen = getComplexMacroValue(macroDef, complexMacroValue);  
	
	//得到使用带参的宏中的传递的值，如MAX(2, (3)) 中的2，(3)
	string single[255] = {""};

	covertCmd(macroDef, single);
	string macroName = single[1];
	string macroRealValue[255] = {""}; 
	int useMacroLen = 0;

	useMacroLen = getComplexMacroRealValue(macroName, useMacro, macroVarNameLen, macroRealValue);

	//展开宏
	for(i=0; i<macroVarNameLen; i++)  //宏参遍历
	{
		for(j=0; j<macroValueLen; j++)  //宏值打散后的数组遍历
		{
			if(macroVarName[i] == complexMacroValue[j]) // 宏参出现，则就传递值代替
			{
				complexMacroValue[j] = macroRealValue[i];   
			}
		}
	}

	//将展开后的宏连成一个字符串
	string replacedMacro = "";
	for(i=0; i<macroValueLen; i++)
	{
		replacedMacro += complexMacroValue[i];
	}
	
	//找到宏在该句中第一次出现的位置
	string temp = useMacro;
	int slen = covertCmd(temp, single);

	int pos[10] = {-1};
	int posCount = -1;
	posCount = isContain(macroName, single, slen, pos);
	if(-1 != posCount)
	{
		for(i=pos[0]; i<pos[0]+useMacroLen; i++)
		{
			single[i] = "";   //将原宏都置为空
		}
		single[pos[0]] = " " + replacedMacro + " ";  // 实现宏替换
	}

	// 将替换后的语句连起来
	string replacedUseMacro = "";
	for(i=0; i<slen; i++)
	{
		single[i] = " " + single[i] + " ";
		replacedUseMacro += single[i];
	}

	return replacedUseMacro;
}


//功能：删除字符串的双引号之间内容, 保留双引号
void delString(string & str)
{
	int pose1,pose2;
	pose1 = str.find("\"");
	while(pose1 != -1)
	{
		pose2 = str.find("\"",pose1+1);
		if(pose2 != -1)
		{
			str.erase(pose1+1, pose2-pose1-1);
		}
		pose1 = str.find("\"", pose2);
	}
}

//功能：删除读取到的代码中的双引号之间的内容
void delCmdString()
{
	int i;
	for(i=0; i<cmdCount; i++)
	{
		delString(command[i]);
	}
}