/* ʵ��5.4�Ĺ��ܣ�ħ������  */

#include"SeedCup2.h"

//���ܣ���#define����������������ħ������
void ghostNum()
{
	int i;
	string temp = "";
	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		if(!checkDef(temp))   // �������#define��䣬����Ҫ�ж��Ƿ���ħ������
		{
			checkNum(temp, i+1);  // �����������е�ħ������
		}
	}
}

//���ܣ�����ַ�������ɢ����ַ������Ƿ���ħ������
//������line���ַ���������
void checkNum(string test, int line)
{
		int i;
		float temp = 0;
		string single[255] = {""};
		int slen = 0;
		slen = covertCmd(test, single);

		for(i=0; i<slen; i++)
		{
			if(onlyNum(single[i]))
			{
				temp = atof(single[i].c_str());
				if(0 != temp && 1 != temp)
				{
					errNum[errLen] = line;
					errType[errLen] = 4;
					errLen++;
				}
			}
		}
}

//���ܣ��ж��ַ����Ƿ�ֻ����С���������
//����ֵ���еĻ�����true
bool isNum(string test)
{
	int len = test.size();
	int i;
	for(i=0; i<len; i++)
	{
		if('.' != test[i] && (test[i] >'9' || test[i]<'0'))
		{
			return false;
		}
	}

	return true;
}

//���ܣ����һ���ַ������Ƿ�ֻ����1���򲻺���С����
//����ֵ���Ƿ���true
bool checkDot(string test)
{
	int i = 0;
	int dot = 0;
	for(i=0; i<test.size(); i++)
	{
		if('.' == test[i])
		{
			dot++;
		}
	}

	if(1 < dot)
	{
		return false;
	}
	else
		return true;

}

