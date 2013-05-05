/* 
	ʵ��5.3.2���ܣ���Ч��֧֮while���(����do...while) 
	while(���ʽ)
*/

#include"SeedCup2.h"

//�����Ч��while��֧
void whileErr()
{
	while1();
	while2();
	while3();
}

//���һ�����ʽΪtrue��false
void while1()
{
	int i;
	string temp = "";
	string single[255] = {""};
	int slen = 0;
	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		slen = covertCmd(temp, single);
		int pos[10] = {0};
		int posCount = isContain("while",single, slen, pos);
		if(-1 != posCount)  // ���йؼ���while
		{
			if(("true" == single[pos[0]+2] || "false" == single[pos[0]+2]) && ")" == single[pos[0]+3])
			{
				errNum[errLen] = i+1;
				errType[errLen] = 3;
				errLen++;
			}
		}
	}
}

//����������ʽΪ����������ʽ ��"-1+(2*3/5)", �����д���С����
void while2()
{
	int i, j;
	string temp = "";
	string single[255] = {""};
	int slen = 0;
	int numFlag = 1;  // �Ƿ�Ϊ����������ı�־, ��Ϊ1������Ϊ��1
	for(i=0; i<cmdCount; i++)
	{
		numFlag = 1;
		temp = command[i];
		slen = covertCmd(temp, single);
		int pos[10] = {0};
		int posCount = isContain("while",single, slen, pos);
		if(-1 != posCount)  // ���йؼ���if
		{
			for(j=pos[0]+1; j<slen; j++) // ����if��������ַ������Ƿ��Ǵ����ֱ��ʽ
			{
				if("(" != single[j] && ")" != single[j] && "[" != single[j] && "]" != single[j] &&
					"{" != single[j] && "}" != single[j] &&
					"+" != single[j] && "-" != single[j] && "*" != single[j] && "/" != single[j]
					&& !onlyNum(single[j]))     // �����ֱ��ʽ���ܳ��ֵ��ַ�, ������������ʱ���Ǵ�����
				{
					numFlag = -1;
					break;
				}
			}
			if(1 == numFlag)
			{
				errNum[errLen] = i+1;
				errType[errLen] = 3;
				errLen++;
			}
		}
	}
}

/*���Ǳ��ʽ�к��б��������*/

//����������ʽ��ֻ��һ�����������Ҹñ�����ֵ��֮ǰ��ֵΪ��ֵ��
void while3()
{
	int begin = 0;
	while(-1 != begin)
	{
		begin = whileFunc3(begin);
	}
}

//���ܣ������������һ�������е�������ж�˼�����ҵ� while��������еı�������Ȼ����while���֮ǰ���ϲ��ң�������һ�γ��ָñ���ʱ��
//+"a=����"���������������"a>��<��>=��<=��!=��+��-��*��/"������������������ϲ飬���ж�Ϊ�ñ����ǲ���ģ������������кܶ��bug�������������
int whileFunc3(int begin)
{
	string func[255] = {""};
	int flen = 0;
	int rowNum = getFunc(func, begin, flen);	

	int i, j, k;
	if(-1 != rowNum)
	{
		int varEqualNum = 0;
		int useFlag = -1;

		string single[255] = {""};
		int slen = 0;
		string temp = "";

		string oneCmdVarName[255] = {""};
		int cmdVarLen = 0;

		int pos[10] = {-1};
		int posCount = -1;
		for(i=0; i<flen; i++)
		{
			temp = func[i];
			slen = covertCmd(temp, single);

			if(isIn("while", single, slen))  // ��func[i]�м�⵽while���
			{
				cmdVarLen = getVarFromOneCmd(begin, temp, oneCmdVarName);  // �õ�while�����б�����

				for(j=0; j<cmdVarLen; j++)    // ����while�����б���
				{
					useFlag = -1;
					varEqualNum = 0;
					for(k=i-1; k>=0; k--)   // ��while���֮ǰ���м������ĸ�ֵ���
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

				if(-1 == useFlag)  // ˵��һֱû�б����䣬��Ч��֧
				{
					errNum[errLen] = rowNum-flen+i+1;
					errType[errLen] = 3;
					errLen++;
				}
			}
		}
	}

	return rowNum;
}


