/* 实现5.1的功能：防止错误赋值 */

#include"SeedCup2.h"

//功能：对所有函数处理错误赋值
void errorAssign()
{
	int begin = 0;
	while(-1 != begin)
	{
		begin = funcErrorAssign(begin);
	}
}

//功能：仅仅对begin位置后的第一个函数进行错误检测
//返回值：返回函数结尾的下一行行号减1的值，－1表示没有找到函数，
int funcErrorAssign(int begin)
{
	int i, j;
	string func[255] = {""};
	string single[255] = {""};  // 打散后的字符串
	int flen = 0; //函数行数 
	int slen = 0; 
	int glen = 0; // 全局变量
	int vlen = 0; // 函数变量
	int rowNum = 0;  // 行号，以0为起始
	rowNum = getFunc(func, begin, flen);
	if(-1 != rowNum)
	{
		string funcVar[255] = {""};  // 函数作用域范围内的变量名
		string globeVar[255] = {""}; // 全局变量名
	
		glen =  getGlobeVar(globeVar);
		vlen = getFuncVar(funcVar, begin);

		int posCount = 0;
		int pos[10] = {-1};

		string checkVar = "";
		string rightVar = "";

		for(i=0; i<flen; i++)
		{
			slen = covertCmd(func[i], single); 
			posCount = isContain("==", single, slen, pos);
			if(-1 != posCount) // 说明存在"=="
			{
				for(j=0; j<posCount; j++)
				{
					checkVar = single[pos[j]-1];
					rightVar = single[pos[j]+1];   // == 右边的字符串，要判断是变量还是常量
					// 左边是变量而且右边是常量就报错, 变量可能是数组，如a[1][0] == 1;
					if(("]" == checkVar || isIn(checkVar, globeVar, glen) || isIn(checkVar, funcVar, vlen)) && (!isIn(rightVar, globeVar, glen) && !isIn(rightVar, funcVar, vlen)))
					{
						errNum[errLen] = (rowNum-flen+i+1);
						errType[errLen] = 1;
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


