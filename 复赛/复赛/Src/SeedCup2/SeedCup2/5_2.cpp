/* 实现5.2功能：指针归空 */

#include"SeedCup2.h"

//功能：对所有函数进行归空检测
void assignNull()
{
	int begin = 0;
	while(-1 != begin)
	{
		begin = funcAssignNull(begin);
	}
}


//功能：仅仅对begin位置后的第一个函数进行归空检测
//返回值：返回函数结尾的下一行行号减1的值，－1表示没有找到函数，
int funcAssignNull(int begin)
{
	int i;
	string func[255] = {""};  // 保存函数行
	string single[255] = {""};  // 打散后的字符串
	int flen = 0; //函数行数 
	int slen = 0; 
	int rowNum = 0;  // 行号，以0为起始
	rowNum = getFunc(func, begin, flen);  // 函数结束行的下一行数减1
	if(-1 != rowNum)
	{
		for(i=0; i<flen; i++)
		{
			slen = covertCmd(func[i], single);

			int posCount = 0;
			int pos[10] = {-1};
			
			string check_p = "";

			posCount = isContain("free", single, slen, pos);

			if(-1 != posCount) // 说明在函数第i行（0起始）存在"free（）函数"
			{
				check_p = single[pos[0]+2];  // 将指针名给check_p
				if(!checkNull(func, flen, i, check_p))  //如果之后没有归空或者使用
				{
					errNum[errLen] = (rowNum-flen+i+1);
					errType[errLen] = 2;
					errLen++;
		//			cout << "line=" << errNum[errLen-1] << ",error=2" << endl; // for debug
				}
					
			}

		}

		return rowNum;
	}

	else
		return -1;
}

//功能：如果在函数func的pos行位置出现的free(check_p),那么在该函数作用域内从pos+1行开始检测, 如果出现没有归空就又
//+操作的情况则报错，一直没有出现check_p = NULL操作也报错。
//参数：func[] 保存函数行的数组， flen 函数行数组长度， pos 出现free的位置（相对函数数组），check_p free的指针
//返回值：true 表示有归空操作
bool checkNull(string func[], int flen, int pos, string check_p)
{
	int i = 0;
	int slen = 0;
	string single[255] = {""};
	for(i=pos+1; i<flen; i++)
	{
		slen = covertCmd(func[i], single);

		int posCount = 0;
		int pos[10] = {-1};
		
		posCount = isContain(check_p, single, slen, pos);

		if((-1 != posCount)) // 说明后面用到了该指针，接下来检测是否是将其归空的操作
		{
			if(("=" == single[pos[0]+1] && "NULL" == single[pos[0]+2]))   // check_p = NULL
				return true;
			else  // 如果不是归空操作就要报错
			{
				if(";" != single[pos[0]+1])    // 如果不是check_p;
					return false;
			}
		}
	}

	return false;
}