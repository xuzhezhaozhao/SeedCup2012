/* ʵ��5.3.4���ܣ���Ч��֧֮for���*/
/*	
	for(i=TEN; i<TEN; i++) 
	ֻ��������򵥵��������������i�ĳ�ֵ������ֵ��С���Եģ��ᵼ��forѭ���޷�ִ��
	������"> < >= <="�����
*/
#include"SeedCup2.h"

//���ܣ������Ч��forѭ��
void forError()
{
	int begin = 0;
	while(-1 != begin)
	{
		begin = forErrorFunc(begin);
	}
}

//���ܣ����һ�������е�forѭ��
//����ֵ:������β��һ�м�1
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
			if(isIn("for", single, slen))    //  �ڸ����м�⵽forѭ��
			{
				//  ">" �����//for(i=10; i>10; i++)
				if("=" == single[3] && onlyNum(single[4]) && ">" == single[7] && onlyNum(single[8]))
				{
					init = atof(single[4].c_str());
					limit = atof(single[8].c_str());
					if(init <= limit)  // ��ֵС������ֵ����Чѭ��
					{
						errNum[errLen] = (rowNum-flen+i+1);
						errType[errLen] = 3;
						errLen++;
					}
				}  // ">"
				//  ">=" �����//for(i=10; i>=10; i++)
				if("=" == single[3] && onlyNum(single[4]) && ">=" == single[7] && onlyNum(single[8]))
				{
					init = atof(single[4].c_str());
					limit = atof(single[8].c_str());
					if(init < limit)  // ��ֵ��������ֵ����Чѭ��
					{
						errNum[errLen] = (rowNum-flen+i+1);
							errType[errLen] = 3;
							errLen++;
					}
				}  // ">="

				//  "<" �����	//for(i=10; i<10; i++)
				if("=" == single[3] && onlyNum(single[4]) && "<" == single[7] && onlyNum(single[8]))
				{
						init = atof(single[4].c_str());
						limit = atof(single[8].c_str());
						if(init >= limit)  // ��ֵ��������ֵ����Чѭ��
						{
							errNum[errLen] = (rowNum-flen+i+1);
							 errType[errLen] = 3;
							 errLen++;
						}
				}  // "<"

				//  "<=" �����	//for(i=10; i<=10; i++)
				if("=" == single[3] && onlyNum(single[4]) && "<=" == single[7] && onlyNum(single[8]))
				{
						init = atof(single[4].c_str());
						limit = atof(single[8].c_str());
						if(init > limit)  // ��ֵ��������ֵ����Чѭ��
						{
							errNum[errLen] = (rowNum-flen+i+1);
							 errType[errLen] = 3;
							 errLen++;
						}
				} // "<="

			}  // �þ��м�⵽forѭ��
		}
	}
	return rowNum;
}