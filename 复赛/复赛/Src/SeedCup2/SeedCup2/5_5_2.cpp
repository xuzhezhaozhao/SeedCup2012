/* ʵ��5.5.2�Ĺ��ܣ�δʹ�õ���Դ֮���� */

#include"SeedCup2.h"


//���ܣ��������ú�
void uselessMacro()
{
	int i=0;
	string temp = "";
	string single[255] = {""};
	string macroName = "";

	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		
		if(checkDef(temp)) // ����Ǻ궨�����
		{
			macroName = getMacroName(temp);  // �õ�����
			if(1 == getMacroCount(macroName))  // ����ִ�������1����û���ù�
			{
				errNum[errLen] = i+1;
				errType[errLen] = 5;
				errLen++;
			}
		}
	}
}

//���ܣ��õ��궨������еĺ���
//����ֵ������
string getMacroName(string test)
{
	string single[50] = {""};
	covertCmd(test, single);
	return single[1];
}


//���ܣ��õ�һ�������ļ���ʹ�õĴ���, "MAX;"�� ��"MAX, 1"��"2, MAX, 1;"������ʹ���˺�
//����ֵ������
int getMacroCount(string test)
{
	int i;
	int count = 0; // �ַ������ֵĴ��� 
	string temp = ""; // ����һ������
	string single[255] = {""};
	int slen = 0;
	int posCount = 0;
	int pos[10] = {-1};
	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		slen = covertCmd(temp, single);
		posCount = isContain(test, single, slen, pos);
		if(-1 != posCount)  // ��������к��и��ַ���
		{
			if(test == single[0] && ("," == single[1] || ";" == single[1]))  // MAX; MAX, 1;
			{
				count = count;
			}
			else
			{
				count = count + posCount;
			}
		}
	}

	return count;
}