/* ʵ��5.5.3�Ĺ��ܣ�δʹ�õ���Դ֮������ */

#include"SeedCup2.h"

//���ܣ����δʹ�õı����������ֲ���ȫ�ֱ���
void uselessVar()
{
	uselessGlobeVar();
	uselessAllFuncVar();
}

//���ܣ����ȫ�ֱ����Ƿ�ʹ��
void uselessGlobeVar()
{
	string globeVar[100] = {""};
	int begin = 0;
	int glen = 0;
	int gPos = 0; // ȫ�ֱ�����λ��
	glen = getGlobeVar(globeVar);
	int gflag = -1;
	for(int i=0; i<glen; i++)
	{
		begin = 0;
		while(-1 != begin)
		{
			begin = isGlobeInFunc(globeVar[i], begin, gflag);
			if(1 == gflag)
			{
				break;
			}
		}
		if(-1 == gflag)   // ��ÿ��������û���õ�
		{
			gPos = getGolbeVarPos(command, cmdCount, globeVar[i]);
			errNum[errLen] = gPos+1;
			errType[errLen] = 5;
			errLen++;
		}
	}
}

//���ܣ����ȫ�ֱ����ں��������ʹ�ã���Ҫ���Ǿֲ�������Ӱ��
//������gfag��ʼΪ��1�������Ϊ��1,˵��ʹ�õ��˸�ȫ�ֱ���
//����ֵ��������������һ�м�1���Ҳ��������򷵻أ�1,
int isGlobeInFunc(string globeVar, int begin, int & gflag)
{
	gflag = -1;
	string func[255] = {""};
	int flen = 0;
	int rowNum = 0;
	rowNum = getFunc(func, begin,  flen);
	if(-1 != rowNum)
	{
		string funcVar[100] = {""};
		int vlen = 0;
		vlen = getFuncVar(funcVar, begin);
		if(!isIn(globeVar, funcVar, vlen))  // �ֲ�����û�и��ǵ����
		{
			if(!isUselessGlobeVar(func, flen, globeVar))  // ����õ���globeVar,������"globeVar;"�������, �Ͱ�gflag��Ϊ1
			{
				gflag = 1;
			}
		}

		return rowNum;
	}
	else
		return -1;
}

//���ܣ�������к�����δʹ�õı���
void uselessAllFuncVar()
{
	int begin = 0;
	while(-1 != begin)
	{
		begin = uselessFuncVar(begin);
	}
}


//���ܣ����һ��������δʹ�õı���
//�������������ҵ���ʼλ��
//����ֵ��������������һ�м�1
int uselessFuncVar(int begin)
{
	string func[255] = {""};
	int flen = 0;
	int rowNum = 0;
	string funcVar[255] = {""};
	int vlen = 0;
	rowNum = getFunc(func, begin, flen);
	if(-1 != rowNum)
	{
		vlen = getFuncVar(funcVar, begin);
		int varPos = 0;

		for(int i=0; i<vlen; i++)
		{
			if(isUselessFuncVar(func, flen, funcVar[i])) // ��������ñ���
			{
				varPos = getFirstAppearPos(func, flen, funcVar[i]);
				errNum[errLen] = rowNum-flen+varPos+1; 
				errType[errLen] = 5;
				errLen++;
			}
		}
		return rowNum;
	}
	else
		return -1;
}

/*
���ܣ����һ�������ں����Ƿ��ù�, ��"int i; i;" �����Ĳ����ù�
1.�Լ�����д
2.������������ֵ
3.��Ӿ�������������ֵ. eg b = p[a]�е�a
˼����Ǽ��������ֵĴ���
����ֵ�����÷���true, �����򷵻�false
*/
bool isUselessFuncVar(string func[], int flen, string varName)
{
	int i;
	int count = 0; // �ַ������ֵĴ��� 
	string temp = ""; // ����һ������
	string single[255] = {""};
	int slen = 0;
	int posCount = 0;
	int pos[10] = {-1};
	for(i=0; i<flen; i++)
	{
		temp = func[i];
		slen = covertCmd(temp, single);
		if(varName == single[0] && ";" == single[1])  // ���ų� "i;"�������
		{
			continue;
		}
		posCount = isContain(varName,single, slen, pos);
		if(-1 != posCount)  // ��������к��и��ַ���
		{
			if((isIn("=", single, slen) || isIn("--", single, slen) || isIn("++", single, slen) || isIn("return", single, slen))
				|| (isIn("int", single, slen) || isIn("float", single, slen) || isIn("char", single, slen) || isIn("double", single, slen) || isIn("long", single, slen)
				|| isIn("short", single, slen) || isIn("signed", single, slen) || isIn("unsigned", single, slen))) // ���б�����������"= ++ --"�ַ��������Ǳ����������
			{
				count = count + posCount;
			}
		}
	}

	if(count > 1)
	{
		return false;
	}
	else
		return true;
}

/*
���ܣ����һ��ȫ�ֱ����ں����Ƿ��ù�
1.�Լ�����д
2.������������ֵ
3.��Ӿ�������������ֵ. eg b = p[a]�е�a
����ֵ�����÷���true, �����򷵻�false
*/bool isUselessGlobeVar(string func[], int flen, string varName)
{
	int i;
	int count = 0; // �ַ������ֵĴ��� 
	string temp = ""; // ����һ������
	string single[255] = {""};
	int slen = 0;
	int posCount = 0;
	int pos[10] = {-1};
	for(i=0; i<flen; i++)
	{
		temp = func[i];
		slen = covertCmd(temp, single);
		if(varName == single[0] && (";" == single[1]))  // ���ų� "i;"
		{
			continue;
		}
		posCount = isContain(varName,single, slen, pos);
		if(-1 != posCount)  // ��������к��и��ַ���
		{
			if((isIn("=", single, slen) || isIn("--", single, slen) || isIn("++", single, slen) || isIn("return", single, slen))
				|| (isIn("int", single, slen) || isIn("float", single, slen) || isIn("char", single, slen) || isIn("double", single, slen) || isIn("long", single, slen)
				|| isIn("short", single, slen) || isIn("signed", single, slen) || isIn("unsigned", single, slen))) // ���б�����������"= ++ --"�ַ��������Ǳ����������
			{
				count = count + posCount;
			}
		}
	}

	if(count > 0)
	{
		return false;
	}
	else
		return true;
}

//���ܣ��õ��������ں����е�һ�γ��ֵ�λ��
//����ֵ��λ�ã�0��ʼ��,�����ڷ��أ�1
int getFirstAppearPos(string func[], int flen, string varName)
{
	int i, j;
	string temp = "";
	int slen = 0;
	string single[255] = {""};
	
	for(i=0; i<flen; i++)
	{
		temp = func[i];
		slen = covertCmd(temp, single);
		for(j=0; j<slen; j++)
		{
			if(varName == single[j])
			{
				return i;
			}
		}
	}

	return -1;
} 

//���ܣ��õ�ȫ�ֱ�������һ�γ��ֵ�λ��
//����ֵ��λ�ã�0��ʼ��,�����ڷ��أ�1
int getGolbeVarPos(string cmd[], int len, string varName)
{
	int i, j;
	string temp = "";
	int slen = 0;
	string single[255] = {""};
	
	for(i=0; i<len; i++)
	{
		temp = cmd[i];
		slen = covertCmd(temp, single);
		for(j=0; j<slen; j++)
		{
			if(varName == single[j])
			{
				return i;
			}
		}
	}

	return -1;
} 