//��������

#include"SeedCup2.h"

//���ܣ��жϸ�������(�������Ѿ��������ַ�����ת����)�ǲ��Ǻ�������(��������)�Ŀ�ͷ����"void main()"��"static int myFunc()"len���ַ����������Ч����
//����ֵ���Ƿ���true
bool isFuncDef(string single[], int len)
{
	if(0 == len)
	{
		return false;
	}
	// ��ͷ�������ͣ���βû�зֺž��Ǻ���������
	else if(isType(single[0]) || "const" == single[0] || "signed" == single[0] || "unsigned" == single[0] || 
			"extern" == single[0] || "static" == single[0] || "void" == single[0])
	{
		if(";" != single[len-1])
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

//���ܣ��жϸ�������(�������Ѿ��������ַ�����ת����)�ǲ��Ǻ�������(���Ƕ���)������ֵ���Ͳ�����const,[un]singed,extern,static����"void myFunc();", len���ַ����������Ч����
//����ֵ���Ƿ���true
bool isFuncState1(string single[], int len)
{
	if(0 == len)
	{
		return false;
	}
	// ��ͷ�������ͣ���β�зֺ�, �ֺ�ǰ�����ţ���3��������
	else if(isType(single[0]) || "void" == single[0] )
	{
		if(";" == single[len-1] && "(" == single[2] && ")" == single[len-2])
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

//���ܣ��жϸ�������(�������Ѿ��������ַ�����ת����)�ǲ��Ǻ�������(���Ƕ���)������ֵ���Ͱ���const,[un]singed,extern,static����"extern void myFunc();", len���ַ����������Ч����
//����ֵ���Ƿ���true
bool isFuncState(string single[], int slen)
{
	int i, j;
	string temp[255] = {""};
	if("extern" == single[0] || "static" == single[0] || "singed" == single[0] || "unsigned" == single[0] || 
		"const" == single[0] )
	{
		j = 0;
		for(i=1; i<slen; i++)
		{
			temp[j] = single[i];
			j++;
		}
		if(isFuncState1(temp, slen-1))
			return true;
	}
	else
	{
		if(isFuncState1(single, slen))
			return true;
	}

	return false;
}

//������ƥ���ѯ�����single�����е����������bracketֵ��1�����Ҵ�������bracketֵ��1
void getBracket(string single[], int len, int & bracket)
{
	int i=0;
	for(i=0; i<len; i++)
	{
		if("{" == single[i])
			bracket++;
		else if("}" == single[i])
			bracket--;
		else
			continue;
	}
}

//С����ƥ���ѯ�����single�����е���С������bracketֵ��1������С������bracketֵ��1
void getLittleBracket(string single[], int len, int & bracket)
{
	int i=0;
	for(i=0; i<len; i++)
	{
		if("(" == single[i])
			bracket++;
		else if(")" == single[i])
			bracket--;
		else
			continue;
	}
}

//�����ַ����Ƿ����������͹ؼ���int,float,double,long,short,char
bool isType(string test)
{
	if("int" == test || "float" == test || "double" == test || "long" == test || "char" == test || "short" == test)
		return true;
	else
		return false;
}

//���ܣ� ָ���ַ����������Ƿ����ָ���ַ�����lenΪ���鳤�ȣ�pos[]���鱣���ַ������ֵ�λ��
//����ֵ�������ڷ��أ�1�������򷵻ظ��ַ������ִ���
int isContain(string str,string contain[], int len, int pos[])
{
	int flag = -1;
	int i, j;
	j = 0;
	
	for(i=0; i<len; i++)
	{
		if(str == contain[i])
		{
			flag = 1;
			pos[j] = i;
			j++;
		}
	}
	if(1 == flag)
		return j;
	else
		return flag;
} 

//ָ���ַ����������Ƿ����ָ���ַ���, �����ִ�Сд��lenΪ���鳤�ȣ������򷵻�true�������ڷ���false
bool isIn(string str,string contain[], int len)
{
	int i;
	for(i=0; i<len; i++)
	{
		if( 0 == _stricmp(str.c_str(), contain[i].c_str()) )
		{
			return true;
		}
	}

	return false;
}

//���ܣ��õ�һ���ַ������ļ����ֵĴ���
//����ֵ������
int getCount(string test)
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
		posCount = isContain(test,single, slen, pos);
		if(-1 != posCount)  // ��������к��и��ַ���
		{
			count = count + posCount;
		}
	}

	return count;
}


//���ܣ�����ַ����Ƿ���#define����
//����ֵ���Ƿ���true
bool checkDef(string test)
{
	string single[255] = {""};
	int slen = 0;
	slen = covertCmd(test, single);

	if("#define" == single[0])
	{
		return true;
	}
	else
	{
		return false;
	}
}

//���ܣ��������Ƚϼ����������Ȱ�one����one��ͬ��two����
//�������������鳤����ͬ��Ϊlen
void sortTwo(int one[], int two[], int len)
{
	int i, j;
	int temp;
	for(i=0; i<len-1; i++)
	{
		for(j=i+1; j<len; j++)
		{
			if(one[i] > one[j])
			{ 
				temp = one[i];
				one[i] = one[j];
				one[j] = temp;

				temp = two[i];
				two[i] = two[j];
				two[j] = temp;
			} 
			else if(one[i] == one[j]) // ��Ȱ�two��������
			{
				if(two[i] > two[j])
				{
					temp = two[i];
					two[i] = two[j];
					two[j] = temp;
				}
			}
			else
				continue;
		}
	}
}

//���ܣ�����ַ����Ƿ�������,����С�������������ŵ�
//����ֵ���Ǿͷ���true
bool onlyNum(string test)
{
	int j;
	int size = test.size();
	if(isNum(test))
	{
		if (checkDot(test))  // �ȼ��С�����Ƿ�ֻ��1����0��
		{
			for(j=0; j<size; j++)
			{
				if( '.' == test[j] || (test[j] >= '0' && test[j] <= '9'))  // ������
				{
					return true;
				}
			}
		}
	}

	return false;
}