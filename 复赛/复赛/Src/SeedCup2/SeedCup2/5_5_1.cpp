/* ʵ��5.5.1�Ĺ��ܣ�δʹ�õ���Դ֮������  */

#include"SeedCup2.h"

//���ܣ�����δʹ�õĺ���
void uselessFunc()
{
	uselessFunc1();
	uselessFunc2();
}

//���ܣ�����δʹ�õĺ�����Դ֮�����ú��������������
void uselessFunc1()
{
	int i;
	int begin = 0;
	string single[255] = {""};
	string temp = "";
	int slen = 0;
	string funcName = "";
	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		slen = covertCmd(temp, single);
		if(isFuncState(single, slen))    // ����Ǻ�������ʱ���д���
		{
			funcName = getFuncName(single, slen);
			if(getCount(funcName) < 3)  // ��������ú���
			{
				errNum[errLen] = i+1;
				errType[errLen] = 5;
				errLen++;
			//	cout << "line=" << errNum[errLen-1] << ",error=5" << endl; // for debug
			}
		}
	}
}

//���ܣ�����δʹ�õĺ�����Դ֮�����ú�����������ֻ�ж�������
void uselessFunc2()
{
	int i;
	int begin = 0;
	string single[255] = {""};
	string temp = "";
	int slen = 0;
	string funcName = "";
	string StaFuncName[255] = {""};  // �к��������ĺ�����
	int sflen = 0;
	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		slen = covertCmd(temp, single);
		if(isFuncDef(single, slen))    // ����Ǻ�������ʱ���д���
		{
			sflen = getStaFuncName(StaFuncName);
			funcName = getFuncName(single, slen);
			if(!isIn(funcName, StaFuncName, sflen)) // �������û������
			{
				if(getCount(funcName) < 2 && "main" != funcName)  // ��������ú���
				{
					errNum[errLen] = i+1;
					errType[errLen] = 5;
					errLen++;
				//	cout << "line=" << errNum[errLen-1] << ",error=5" << endl; // for debug
				}
			}
		}
	}
}


//���ܣ��õ������������������еĺ�����
//����ֵ���õ��ĺ�����
string getFuncName(string single[], int slen)
{
	int i = 0;
	string funcName = "";
	while("(" != single[i])
	{
		i++;
	}

	funcName = single[i-1];

	return funcName;
}

//���ܣ����������ĺ�����������������StaFuncName��
//����ֵ�����鳤��
int getStaFuncName(string StaFuncName[])
{
	int i=0;
	int nlen = 0;
	string temp = "";
	string single[255] = {""};
	int slen = 0;
	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		slen = covertCmd(temp, single);
		if(isFuncState(single, slen)) // ����Ǻ�������
		{
			StaFuncName[nlen] = getFuncName(single, slen);
			nlen++;
		}
	}

	return nlen;
}
