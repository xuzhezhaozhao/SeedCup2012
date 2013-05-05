/* ʵ���Զ���Ĺ���: 
1������ڴ��Ƿ�й©
	1.1��malloc�����ڴ棬û��free����ڴ档
	1.2����ָ��ָ��malloc�����ڴ棬��û���ͷ�����ڴ�֮ǰ�ı��˸õ�ָ���ֵ��ʹ�ÿ��ڴ��޷��ͷ�, ����̬����freeָ���ֵ������
		int *p1 = (int)malloc(sizeof(int));
		int *p2 = (int)malloc(sizeof(int));	
		p1 = p2;
		free(p1);
	��Ȼp2���ڴ������p1��ԭ���ͷ��ˣ����ǻ���Ҫ��p2������������

	����λ�ã���malloc�ڴ��λ��
	������룺7
*/

#include"SeedCup2.h"

/*
���ܣ�������к����е��ڴ�й©�����
���ǵ����������ָ��ָ����ڴ棬û��free, mallocʱ��ָ��ָ��
*/
void memoryLeak()
{
	int begin = 0;
	while(-1 != begin)
	{
		begin = memoryLeakFunc(begin);
	}
	memLeakGlober();  // ȫ�ֱ������ڴ�й©
}

//���ܣ����һ�������е��ڴ�й©����
int memoryLeakFunc(int begin)
{
	int rowNum = memoryLeakFunc1(begin);
	memoryLeakFunc2(begin);

	return rowNum;
}

//���ܣ����һ�������е��ڴ�й©���� 1.1��malloc�����ڴ棬û��free����ڴ档
int memoryLeakFunc1(int begin)
{
	string func[255] = {""};
	int flen = 0;
	int rowNum = -1;
	rowNum =  getFunc(func, begin, flen);

	if(-1 != rowNum)   // �����ȡ���˺���
	{
		int i, j;
		string temp = "";
		string single[255] = {""};
		int slen = 0;
		for(i=0; i<flen; i++)
		{
			temp = func[i];
			slen = covertCmd(temp, single);
			// ��"malloc"û��"="�����
			if(isIn("malloc", single, slen) && !isIn("=", single, slen))  
			{
				errNum[errLen] = (rowNum-flen+i+1);
				errType[errLen] = 7;
				errLen++;
			}
			//��"malloc", ��"="�����
			if(isIn("malloc", single, slen) && isIn("=", single, slen))
			{
				int freeFlag = -1;
				int pos[10] = {-1};
				int posCount = -1;
				posCount = isContain("=", single, slen, pos);
				string pFree = single[pos[0]-1];
				for(j=i+1; j<flen; j++)
				{
					temp = func[j];
					slen = covertCmd(temp, single);
					if(isIn("free", single, slen) && isIn(pFree, single, slen))  // free��pFreeָ���ָ��
					{
						freeFlag = 1;
						break;
					}
				}
				if(-1 == freeFlag)   // ���û��free
				{
					errNum[errLen] = (rowNum-flen+i+1);
					errType[errLen] = 7;
					errLen++;
				}
			}
		}

		return rowNum;
	}
	return -1;
}

//���ܣ����һ�������е��ڴ�й©���� 1.2����ָ��ָ��malloc�����ڴ棬��û���ͷ�����ڴ�֮ǰ�ı��˸õ�ָ���ֵ��ʹ�ÿ��ڴ��޷��ͷ�.
//�ı�ֵ����ʽ��ָ�룭ָ�룬ָ�룭��������ָ�룭����ȡַ��&��
int memoryLeakFunc2(int begin)
{
	string func[255] = {""};
	int flen = 0;
	int rowNum = -1;
	rowNum =  getFunc(func, begin, flen);
	string pointName[255] = {""};
	
	if(-1 != rowNum)   // �����ȡ���˺���
	{
		int pointLen = getPointName(func, flen, pointName);

		int i, j, k;
		string temp = "";
		string single[255] = {""};
		int slen = 0;
		for(i=0; i<flen; i++)
		{
			temp = func[i];
			slen = covertCmd(temp, single);
			//��"malloc", ��"="�����
			if(isIn("malloc", single, slen) && isIn("=", single, slen))
			{
				int freeFlag = -1;
				int pos[10] = {-1};
				int posCount = -1;
				posCount = isContain("=", single, slen, pos);
				string pFree = single[pos[0]-1];
				for(j=i+1; j<flen; j++)
				{
					temp = func[j];
					slen = covertCmd(temp, single);
					if(isIn("free", single, slen) && isIn(pFree, single, slen))
					{
						freeFlag = 1;
						break;
					}
					if(isIn(pFree, single, slen) && isIn("&", single, slen) && isIn("=", single, slen))
					{
						// ����  p=&a; ��������ı�ָ���ֵ
						errNum[errLen] = (rowNum-flen+i+1);
						errType[errLen] = 7;
						errLen++;
						break;
					}
					int tempFlag = -1;
					for(k=0; k<pointLen; k++)
					{
						int pos[10] = {-1};
						int posCount = -1;
						posCount = isContain(pFree, single, slen, pos);
						if(-1 != posCount)
						{
							if("=" == single[pos[0]+1])
							{
								if(pFree != single[pos[0]+2])   // �ų�p1 = p1;�����
								{
									// ����p1 = p2, p1=a; ֮������, ���һ�ҪpFreeҪ�ڣ��Ⱥ����
									errNum[errLen] = (rowNum-flen+i+1);
									errType[errLen] = 7;
									errLen++;
									tempFlag = 1;
									break;
								}
							}
						}
					}
					if(1 == tempFlag)
					{
						break;
					}
				}
				
			}
		}
	}
	return rowNum;
}

//���ܣ��õ����������е�ָ�������������������
//����ֵ�����鳤��
int getPointName(string func[], int flen, string pointName[])
{
	int pointLen = 0;
	int i;

	string single[255] = {""};
	int slen = 0;
	int pos[10] = {-1};
	int posCount = -1;
	for(i=0; i<flen; i++)
	{
		slen = covertCmd(func[i], single);
		if(isType(single[0]))
		{
			posCount = isContain("*", single, slen, pos); // ָ��
			if(-1 != posCount)
			{
				pointName[pointLen] = single[pos[0]+1];
				pointLen++;
			}
			posCount = isContain("[", single, slen, pos); // ����
			if(-1 != posCount)
			{
				pointName[pointLen] = single[pos[0]-1];
				pointLen++;
			}
		}
	}
	return pointLen;
}

//���ܣ��õ�ȫ�ֱ����е�ָ������������������
//����ֵ�����鳤��
int getGloblePointName(string globePointName[])
{
	int i;
	string temp = "";
	string single[255] = {""};
	int slen = 0;

	int glen = 0; //ȫ�ֱ������鳤��
	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		slen = covertCmd(temp, single);

		if(!isFuncDef(single, slen))   // ������һ����������˵��֮��û��ȫ�ֱ�����������
		{
			if(isIn("*", single, slen) || isIn("[", single, slen))  // ��"*"��"["˵����ָ�������
			{
				getVar(temp, globePointName, glen);
			}
		}
		else
		{
			break;
		}
	}
	return glen;
}

//���ܣ��õ�ȫ�ֱ����п����ڴ��ָ����
//����ֵ�����鳤��
int getGloberMalloc(string globeMallocName[])
{
	int i;
	string temp = "";
	string single[255] = {""};
	int slen = 0;

	int glen = 0; //ȫ�ֱ������鳤��
	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		slen = covertCmd(temp, single);

		if(!isFuncDef(single, slen))   // ������һ����������˵��֮��û��ȫ�ֱ�����������
		{
			if(isIn("*", single, slen) && isIn("malloc", single, slen))  // ��"*"��"malloc"˵�������ڴ�
			{
				getVar(temp, globeMallocName, glen);
			}
		}
		else
		{
			break;
		}
	}
	return glen;
}

//���ܣ����ȫ�ֱ��������ڴ��Ƿ��ͷţ������Ǿֲ��������ǵ�Ӱ��
void memLeakGlober()
{
	int i, j;
	int memLeakFlag = -1;  // ��й©���ǣ�1
	string globeMallocName[255] = {""};
	int globerMallocVarLen = getGloberMalloc(globeMallocName);

	string temp = "";
	string single[255] = {""};
	int slen = 0;
	for(i=0; i<globerMallocVarLen; i++)
	{
		for(j=0; j<cmdCount; j++)
		{
			temp = command[j];
			slen = covertCmd(temp, single);
			if(isIn("free", single, slen) && isIn(globeMallocName[i], single, slen)) // �ͷ���
			{
				memLeakFlag = 1; 
				break;
			}
			if(globeMallocName[i] == single[0] && "=" == single[1])
			{
				memLeakFlag = -1;   // δ�ͷž͸ı�����ֵ
				break;
			}
		}
		if(-1 == memLeakFlag)  // �����ڴ�й©
		{
			//���Ҹ�ȫ�ֱ�����λ��
			for(j=0; i<cmdCount; j++)
			{
				temp = command[j];
				slen = covertCmd(temp, single);
				if(isIn(globeMallocName[i], single, slen))
				{
					errNum[errLen] = j+1;
					errType[errLen] = 7;
					errLen++;
					break;
				}
			}
		}
	}
}