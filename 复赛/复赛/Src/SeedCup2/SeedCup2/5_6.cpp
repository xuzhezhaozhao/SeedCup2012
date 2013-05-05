/* ʵ��5.6�Ĺ���: ������ϵ����ͼ(�򵥼��ݹ�) */

#include"SeedCup2.h"

/*
���ܣ����ݵ������ó��Ķ�άͼ��Ҫ��ĸ�ʽ��ӡ����������ͼ
*/
void getGraphic(string step[][100])
{

	int i, j;
	int tempLen = 0;  // ÿһ���е���Ч�ַ�����
	int mainLen = graphStep3(step);
	for(i=0; i<mainLen; i++)
	{
		tempLen = getMainEdgeNum(i, step)+1;
		for(j=0; j<tempLen; j++) // ���Ϊ"*"��Ҫ���ǣ�����ӡ���������һ����������Ҫ��'-'��
		{
			if("*" == step[i][j+1])
			{
				cout << step[i][j];
				break;
			}
			else if(tempLen-1 == j)
			{
				cout << step[i][j];
			}
			else
			{
				covertStep(step[i][j]);
				cout << step[i][j];
			}
		}	
		cout << endl;
	}
}

/*
���ܣ���һ���������ȵõ�ָ����������(������main����)�ĵ��ù�ϵ, ������ʽ, ��ʾf1����f2��f3, ���������һ����ά����step1[][100](�ж��ٵ��ú������ж�����)��
f1 f2
#  f3
����ֵ����ά���������������ú�������
*/
int graphStep1(string funcName, string step1[][100])
{
	int i;
	string tempInFuncName[255] = {""}; // ���õĺ�����, ������
	int tempInLen = getFuncName(tempInFuncName, funcName);

	string inFuncName[255] = {""};
	int inLen = delRepeat(tempInFuncName, tempInLen, inFuncName); // ɾ����������
	sortStringIncr(inFuncName, inLen);   //��������

	for(i=0; i<inLen; i++)
	{
		if(0 == i)
		{
			step1[i][0] = funcName;
		}
		else
		{
			step1[i][0] = "#";
		}
		step1[i][1] = inFuncName[i];
	}
	return inLen;
}

/*
���ܣ��ڶ������õ�main�����ĵ��ù�ϵ, ��main������ά��Ӧ�ø��󣬶���Ϊ100*100�ģ������ʼ��Ϊ��
����ֵ����ά���������������ú�������
*/
int graphStep2(string funcName, string step2[][100])
{
	int i;
	string tempInFuncName[255] = {""}; // ���õĺ�����, ������
	int tempInLen = getFuncName(tempInFuncName, funcName);

	string inFuncName[255] = {""};
	int inLen = delRepeat(tempInFuncName, tempInLen, inFuncName); // ɾ����������
	sortStringIncr(inFuncName, inLen);   //��������

	for(i=0; i<inLen; i++)
	{
		if(0 == i)
		{
			step2[i][0] = funcName;
		}
		else
		{
			step2[i][0] = "#";
		}
		step2[i][1] = inFuncName[i];
	}
	return inLen;
}

/*
���ܣ�������, ���������������Ķ�ά��������ͼ������"#"����10��"-","*"��ʾ�գ���־�ݹ�Ľ���
����ֵ����άͼ������
*/
int graphStep3(string step3[][100])
{
	int i;
	int mainLen = graphStep2("main", step3);   //�����������ĵ������
	for(i=0; i<mainLen; i++)
	{
		if(isInvokeFunc(getMainEdge(i, step3)))
		{
			mainLen = insertNewFunc(step3, mainLen, i);
			isRecursive(step3, i);
			i--;  //i��1ȥ�ж�����һ�����ӵ�һ��������û�е�����������
		}
	}

	return mainLen;
}


//���ܣ��õ�ָ���������õĺ���������������������������funcName������
//����ֵ�����鳤��
int getFuncName(string funcName[], string thisFuncName)
{
	string func[255] = {""};
	int flen = 0;
	getFuncFromName(func, flen, thisFuncName);   // ���ú�������

	string single[255] = {""};
	int slen = 0;	
	
	int fnlen = 0; //���ú�������
	for(int i=1; i<flen; i++)   //������������һ�����ų���
	{
		getFuncNameFromCmd(func[i], funcName, fnlen);
	}
	return fnlen;
}

//���ܣ��õ�һ������еĺ�����, ���׷�Ӵ���funcNameFromCmd[]��, len������֮ǰ�ĳ���
void getFuncNameFromCmd(string cmd, string funcNameFromCmd[], int & len)
{
	int slen = 0;
	string single[255] = {""};
	slen = covertCmd(cmd, single);
	string allFuncName[255] = {""};
	int tempType[255] = {0};

	int fnlen = getFuncName(allFuncName, tempType);  // �õ�ȫ������������
	haveGet(allFuncName, fnlen, single, slen, funcNameFromCmd, len);  //�������еĺ�����׷�Ӵ���funcNameFromCmd[]��
}

//���ܣ�ȥ���ַ����������ظ����ַ���,��������clean[]��
//������len��test[]����
//���أ�clean����
int delRepeat(string test[], int len, string clean[])
{
	int i;
	int clen = 0;
	for(i=0; i<len; i++)
	{
		if(!isIn(test[i], clean, clen))
		{
			clean[clen] = test[i];
			clen++;
		}
	}
	return clen;
}

//���ܣ���ָ����string���������򣬳���Ϊlen
void sortStringIncr(string str[], int len)
{
	int i, j;
	string temp;
	for(i=0; i<len-1; i++)
	{
		for(j=i+1; j<len; j++)
		{
			if(str[i] > str[j])
			{
				temp = str[i];
				str[i] = str[j];
				str[j] = temp;
			}
		}
	}
}

//���ܣ��ж�ָ�������Ƿ��������������
//����ֵ�������˷���true, û�е��÷���false
bool isInvokeFunc(string funcName)
{
	string step1[20][100] = {""};
	int len = graphStep1(funcName, step1);
	if(0 == len)  // û�е���
	{
		return false;
	}
	else
		return true;

}

//���ܣ��õ�main������ά��ͼ��row�У�0��ʼ��δβԪ�ص�ֵ
//����ֵ��δβ�ַ���
string getMainEdge(int row, string step[][100])
{
	int edge = 0;
	while("" != step[row][edge])
	{
		edge++;
	}

	if(0 != edge)
		return step[row][edge-1];
	else
		return "";
}

//���ܣ��õ�main������ά��ͼ��row�У�0��ʼ��δβԪ�ص��кţ�0��ʼ��
//����ֵ��δβ�к�
int getMainEdgeNum(int row, string step[][100])
{
	int edge = 0;
	while("" != step[row][edge])
	{
		edge++;
	}
	return (edge-1);
}

//���ܣ���main��άͼδ�˲����µ��ز��ṹ
//����ֵ����άͼ����Ч����
int insertNewFunc(string step[][100], int stepLen, int row)
{
	int i, j;
	int tempNum = 0;
	string funcEdge = getMainEdge(row, step);  // �õ�δ�˺�������OK
	string step1[20][100] = {""};
	int funcEdgeLen = graphStep1(funcEdge, step1);  //�õ����ú����ĵ��ù�ϵ��������

	/* row�к������funcEdgeLen��1�� */
	for(i=stepLen-1; i>row; i--)
	{
			for(j=0; j<100; j++)
			{
				step[i+funcEdgeLen-1][j] = step[i][j];
			}
	}

	/* ��ԭ�����Ƶ���λ���� "#" */
	tempNum = getMainEdgeNum(row, step)+1;
	for(i=row+1; i<row+funcEdgeLen; i++)
	{
		for(j=0; j<tempNum; j++)
		{
			step[i][j] = "#";
		}
	}

	tempNum = getMainEdgeNum(row, step);
	j = 0;
	for(i=row; i<(row+funcEdgeLen); i++)
	{
		step[i][tempNum+1] = step1[j][1];
		j++;
	}

	return (stepLen+funcEdgeLen-1);
}


//���ܣ��ж���row���Ƿ�����˵ݹ�, ˼������ж��ڸ�ά�����һ���ַ����Ƿ��ǰ�����ͬ����ͬ���ǵݹ飬
//+�����ݹ�����һ���ַ����ĺ�һ���ַ�����Ϊ "*",���Խ����ݹ�
void isRecursive(string step[][100], int row)
{
	int len = getMainEdgeNum(row, step)+1;  //�õ���ά�ϵ��ַ�������
	for(int i=0; i<len-1; i++)
	{
		if(step[row][len-1] == step[row][i])  //���ֵݹ�
		{
			step[row][len] = "*"; // �����һ����Ϊ"*"
		}
	}
}


//���ܣ���Ҫ��ת����άͼ�е��ַ�����"#"���10��"-", ���������룬"*"ת�ɿ�
void covertStep(string & str)
{
	int i;
	if("#" == str)
		str = "----------";
	else if("*" == str)
		str = "";
	else 
	{
		if("" != str)
		{
			int size = str.size();
			for(i=size; i<10; i++)
			{
				str = str + "-";
			}
		}
	}
}