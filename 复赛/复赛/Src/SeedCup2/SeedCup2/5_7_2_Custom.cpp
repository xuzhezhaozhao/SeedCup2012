/*
ʵ���Զ���Ĺ���: 
2���������Ƿ�δ����ֵ��ʹ����
	�磺int i;
		int j = i;
	����λ�ã������������ĵط�����
	������룺8

	���Ľ����������ʹ��ǰ�Ƿ񸳳�ֵ��û��ʵ��
*/
#include"SeedCup2.h"

//���ܣ�������к����ı�����ʹ��ǰ�Ƿ��˳�ֵ�������ȫ�ֱ���
void noInitialVar()
{
	int begin = 0;
	while(-1 != begin)
	{
		begin = noInitialVarFunc(begin);
	}
	noInitialGolberVar();
}

//���ܣ����һ�������еı�����ʹ��ǰ�Ƿ��˳�ֵ,����˼����Ǽ��һ��������һ�γ���ʱ����Ƿ���"=", �ǵĻ��Ͳ��ټ�飬���ǵĻ��ͼ�����ڶ��γ���ʱ����Ƿ��ǵ�"="
//����ֵ��������β��һ��������1
int noInitialVarFunc(int begin)
{
	int i, j, k;
	string func[255] = {""};
	int flen = 0;
	int rowNum = getFunc(func, begin, flen);
	if(-1 != rowNum)
	{
		string funcVarName[255] = {""};
		int vlen = getFuncVar(funcVarName, begin);

		string single[255] = {""};
		int slen = 0;

		int pos[10] = {-1};
		int posCount = -1;
		for(i=0; i<vlen; i++)  // Ҫ����һ���ж�γ��ֱ������������for�����
		{
			int tempFlag = -1;   //�����Ƿ�ֵ�ı�־
			for(j=0; j<flen; j++)
			{
				tempFlag = -1;
				slen = covertCmd(func[j], single);
				posCount = isContain(funcVarName[i], single, slen, pos);
				if(1 == posCount)   // �����ڸ��г���һ��
				{
					if("=" == single[pos[0]+1])  // j�б�������ʱ��ֵ�ˣ�����Ҫ�ټ��
					{
						break;
					}
					else // ��������ʱû�и�ֵ��������飬�´γ���ʱһ��Ҫ��ֵ
					{
						for(k=j+1; k<flen; k++)
						{
							slen = covertCmd(func[k], single);
							posCount = isContain(funcVarName[i], single, slen, pos);
							if(-1 != posCount)   // k�еڶ��γ��ֱ���
							{
								if("=" != single[pos[0]+1])   // ����ڶ���û�и�ֵ�ͱ���
								{
									errNum[errLen] = (rowNum-flen+j+1);
									errType[errLen] = 8;
									errLen++;	
								}
								tempFlag = 1;
								break;   //�ڶ��γ����˱���������
							}
						}
					}

					if(1 == tempFlag)
						break;
				}
			}   //��������
		} //����������
	}
	return rowNum;
}

//���ܣ����ȫ�ֱ����Ƿ�δ����ֵ��ʹ��
void noInitialGolberVar()
{
	int i,j, k;
	string globeVar[255] = {""};
	int glen = getGlobeVar(globeVar);
	string single[255] = {""};
	int slen = 0;

	int pos[10] = {-1};
	int posCount = -1;
	for(i=0; i<glen; i++)  // Ҫ����һ���ж�γ��ֱ������������for�����
	{
		int tempFlag = -1;   //�����Ƿ�ֵ�ı�־
		for(j=0; j<cmdCount; j++)
		{
			tempFlag = -1;
			slen = covertCmd(command[j], single);
			posCount = isContain(globeVar[i], single, slen, pos);
			if(1 == posCount)   // �����ڸ��г���һ��
			{
				if("=" == single[pos[0]+1])  // j�б�������ʱ��ֵ�ˣ�����Ҫ�ټ��
				{
					break;
				}
				else // ��������ʱû�и�ֵ��������飬�´γ���ʱһ��Ҫ��ֵ
				{
					for(k=j+1; k<cmdCount; k++)
					{
						slen = covertCmd(command[k], single);
						posCount = isContain(globeVar[i], single, slen, pos);
						if(-1 != posCount)   // k�еڶ��γ��ֱ���
						{
							if("=" != single[pos[0]+1])   // ����ڶ���û�и�ֵ�ͱ���
							{
								errNum[errLen] = j+1;
								errType[errLen] = 8;
								errLen++;	
							}
							tempFlag = 1;
							break;   //�ڶ��γ����˱���������
						}
					}
				}

				if(1 == tempFlag)
					break;
			}
		}   //��������
	} //����������
}