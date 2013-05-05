/* ʵ��5.3.3���ܣ���Ч��֧֮switch���*/

#include"SeedCup2.h"

//���ܣ������Ч��switch��֧
void switchErr()
{
	int begin = 0;
	while(-1 != begin)
	{
		begin = switchInfunc(begin);
	}
}

//���ܣ��õ�һ�������еĴ�ָ��λ�ò��ҵ���һ��switch�����������������������
//������begin�ǴӺ����ĵڼ��п�ʼ���ң�switchLen��switch���ĳ���
//����ֵ���������switch��β��һ�м�1
int getOneSwitch(string func[], int flen, int begin, string switchCmd[], int & switchLen)
{
	int i=0;
	int j=0;
	int k=0;
	switchLen = 0;
	string single[100] = {""};
	string temp = "";
	int slen = 0;
	int bracket = 0;  // ������ƥ����

	for(i=begin; i<flen; i++)
	{
		temp = func[i];
		slen = covertCmd(temp, single);

		if("switch" == single[0] && ";" != single[slen-1]) // �ж��Ƿ���switch���Ŀ�ʼ
		{
			// switch���Ŀ�ʼ��������ɺ��Ҫbreak�����
			bracket = 0;  //������ƥ��ֵ��ʼΪ0
			j = 0;
			for(k=i; k<flen; k++)
			{
				switchCmd[j] = func[k];   // �Ƚ����и���switchCmd[j]
				switchLen = j+1;
				j++;
				temp = func[k];
				slen = covertCmd(temp, single);

				if(k == i && "}" == single[slen-1])
				{
					return (k+1);
				}
				else
				{
					getBracket(single, slen, bracket); // �õ�������ƥ�����

					if(k!=i && 0 == bracket)   // ������ƥ����ɣ�˵��switch������
					{
						return (k+1);
					}
					else // û��ƥ�������˵��switch��仹û�н���
					{
						continue;
					}
				}
			}
		}
	}

	return -1;
}

//���ܣ���һ�������м����Ч��switch���
//����ֵ�����غ�����β��һ�м�1
int switchInfunc(int beginFunc)
{
	string func[255] = {""};
	int flen = 0;
	int rowNum = getFunc(func, beginFunc, flen);	

	int i, j, k;
	if(-1 != rowNum)
	{
		int	useFlag = -1;
		int varEqualNum = 0;

		string switchValue = "";  // switch ��ֵ

		string temp = "";
		string single[255] = {""};
		int slen = 0;
		string oneCmdVarName[255] = {""};
		int oneCmdVarLen = 0;
		string switchCmd[255] = {""};
		int switchLen = 0;
		int beginInfunc = 0;

		int pos[10] = {-1};
		int posCount = -1;
		for(i=0; i<flen; i++)
		{
			temp = func[i];
			slen = covertCmd(temp, single);
			if(isIn("switch", single, slen)) //�ں�����i��λ�� ��⵽switch���
			{
				beginInfunc = i;
				int switchPos = getOneSwitch(func, flen, beginInfunc, switchCmd, switchLen); // �õ���һ��switch���
				temp = switchCmd[0];  // switch
				slen = covertCmd(temp, single);
				oneCmdVarLen = getVarFromOneCmd(beginFunc, switchCmd[0], oneCmdVarName);// �õ�switch�еı�����
				if(1 == oneCmdVarLen)  //switch��ֻ��һ������ʱ
				{
					for(j=0; j<oneCmdVarLen; j++)    // ����switch�����б���
					{
						useFlag = -1;
						varEqualNum = 0;
						for(k=i-1; k>=0; k--)   // ��switch���֮ǰ���м������ĸ�ֵ���
						{
							temp = func[k];
							slen = covertCmd(temp, single);
							posCount = isContain(oneCmdVarName[j], single, slen, pos);
							int m = 0; // ������һ���г��ֵĴ�������
							if(-1 != posCount)   // ��������˱���, ��������ֱ�����λ���ǲ���a=1�ļ���ʽ
							{
								for(m=posCount-1; m>=0; m--) // ��һ�����ʼ��������
								{
									//single[pos[m]+1] ������ĵ�һ���ַ�
									if(">" == single[pos[m]+1] || "<" == single[pos[m]+1] || ">=" == single[pos[m]+1] || 
										"<=" == single[pos[m]+1] || "!=" == single[pos[m]+1] || "+" == single[pos[m]+1] || "-" == single[pos[m]+1] ||
										"*" == single[pos[m]+1] || "/" == single[pos[m]+1])
									{
										continue;
									}
									if("=" == single[pos[m]+1] && onlyNum(single[pos[m]+2])) // a = ���� �����
									{
										switchValue = single[pos[m]+2]; // �õ�switch��ֵ
										varEqualNum = 1;
										break;
									}
									else
									{
										varEqualNum = -1;
										break;
									}
								}
								if(1 == varEqualNum || -1 == varEqualNum) // ���continue�˾�Ҫ��������һ�У��������˳�forѭ��
									break;
							}	
						}

						if(-1 == varEqualNum)
						{
							// ˵���б������
							useFlag = 1;
							break;   // ������Ч��ȥ
						}
					}
					int defaultFlag = -1;
					if(-1 == useFlag)  // ˵��һֱû�б����䣬��Ч��֧
					{
						defaultFlag = -1;
						for(k=0; k<switchLen; k++)
						{
							temp = switchCmd[k];
							slen = covertCmd(temp, single);
							if(isIn("case", single, slen))  // ����case ��֧
							{
								if(switchValue != single[1]) // ����һ�е�caseֵ����switch��ʱ���򱨴�
								{
									errNum[errLen] = (rowNum-flen+i+1+k);
									errType[errLen] = 3;
									errLen++;
								}
								else   // caseֵ��switchֵʱ��˵��defaultҲҪ����
									defaultFlag = 1;
							}
						}
						for(k=0; k<switchLen; k++)
						{
							temp = switchCmd[k];
							slen = covertCmd(temp, single);
							if(isIn("default", single, slen) && 1 == defaultFlag)  // ����case ��֧
							{
								errNum[errLen] = (rowNum-flen+i+1+k);
								errType[errLen] = 3;
								errLen++;
							}
						}
					}
				}//switch��ֻ��һ������ʱ
				
				int defaultFlag = -1;
				if(0 == oneCmdVarLen)  // ˵��switch����û�б���
				{
					temp = switchCmd[0];
					slen = covertCmd(temp, single);
					if(onlyNum(single[2]) && ")" == single[3])   // switch(1) ����ʽ
					{
						switchValue = single[2];
						defaultFlag = -1;
						for(k=0; k<switchLen; k++)
						{
							temp = switchCmd[k];
							slen = covertCmd(temp, single);
							if(isIn("case", single, slen))  // ����case ��֧
							{
								if(switchValue != single[1]) // ����һ�е�caseֵ����switch��ʱ���򱨴�
								{
									errNum[errLen] = (rowNum-flen+i+1+k);
									errType[errLen] = 3;
									errLen++;
								}
								else   // caseֵ��switchֵʱ��˵��defaultҲҪ����
									defaultFlag = 1;
							}
						}
						for(k=0; k<switchLen; k++)
						{
							temp = switchCmd[k];
							slen = covertCmd(temp, single);
							if(isIn("default", single, slen) && 1 == defaultFlag)  // ����case ��֧
							{
								errNum[errLen] = (rowNum-flen+i+1+k);
								errType[errLen] = 3;
								errLen++;
							}
						}
					}
				}
			}   // ��⵽switch��λ��
		}
	}
	return rowNum;
}