/* 实现5.3.4功能：无效分支之for语句*/
/*	
	for(i=TEN; i<TEN; i++) 
	只考虑了最简单的这种情况，就是i的初值与限制值大小不对的，会导致for循环无法执行
	考虑了"> < >= <="的情况
*/
#include"SeedCup2.h"

//功能：检测无效的for循环
void forError()
{
	int begin = 0;
	while(-1 != begin)
	{
		begin = forErrorFunc(begin);
	}
}

//功能：检测一个函数中的for循环
//返回值:函数结尾下一行减1
int forErrorFunc(int begin)
{
	string func[255] = {""};
	int flen = 0;
	int rowNum = getFunc(func, begin, flen);	
	
	string temp = "";
	string single[255] = {""};
	int slen = 0;
	int i;
	int init = 0;
	int limit = 0;
	if(-1 != rowNum)
	{
		for(i=0; i<flen; i++)
		{
			temp = func[i];
			slen = covertCmd(temp, single);
			if(isIn("for", single, slen))    //  在该行中检测到for循环
			{
				//  ">" 的情况//for(i=10; i>10; i++)
				if("=" == single[3] && onlyNum(single[4]) && ">" == single[7] && onlyNum(single[8]))
				{
					init = atof(single[4].c_str());
					limit = atof(single[8].c_str());
					if(init <= limit)  // 初值小于限制值，无效循环
					{
						errNum[errLen] = (rowNum-flen+i+1);
						errType[errLen] = 3;
						errLen++;
					}
				}  // ">"
				//  ">=" 的情况//for(i=10; i>=10; i++)
				if("=" == single[3] && onlyNum(single[4]) && ">=" == single[7] && onlyNum(single[8]))
				{
					init = atof(single[4].c_str());
					limit = atof(single[8].c_str());
					if(init < limit)  // 初值大于限制值，无效循环
					{
						errNum[errLen] = (rowNum-flen+i+1);
							errType[errLen] = 3;
							errLen++;
					}
				}  // ">="

				//  "<" 的情况	//for(i=10; i<10; i++)
				if("=" == single[3] && onlyNum(single[4]) && "<" == single[7] && onlyNum(single[8]))
				{
						init = atof(single[4].c_str());
						limit = atof(single[8].c_str());
						if(init >= limit)  // 初值大于限制值，无效循环
						{
							errNum[errLen] = (rowNum-flen+i+1);
							 errType[errLen] = 3;
							 errLen++;
						}
				}  // "<"

				//  "<=" 的情况	//for(i=10; i<=10; i++)
				if("=" == single[3] && onlyNum(single[4]) && "<=" == single[7] && onlyNum(single[8]))
				{
						init = atof(single[4].c_str());
						limit = atof(single[8].c_str());
						if(init > limit)  // 初值大于限制值，无效循环
						{
							errNum[errLen] = (rowNum-flen+i+1);
							 errType[errLen] = 3;
							 errLen++;
						}
				} // "<="

			}  // 该句中检测到for循环
		}
	}
	return rowNum;
}