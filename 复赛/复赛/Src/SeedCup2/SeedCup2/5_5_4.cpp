/* ʵ��5.5.4�Ĺ��ܣ�δʹ�õ���Դ֮������ֵ */

#include"SeedCup2.h"

//���ܣ����ÿһ�������ĵ��ú����Ƿ��õ���������ֵ
void uselessReturn()
{
	useReturnOfMalloc(); // �������malloc
	int begin = 0;
	while(-1 != begin)
	{
		begin = uselessReturnFunc(begin);
	}
}

//���ܣ����һ�������еĵ��ú����Ƿ��õ���������ֵ
//����ֵ������������һ�м�1��û�к����򷵻أ�1
int uselessReturnFunc(int begin)
{
	string func[255] = {""};
	int flen = 0;
	int rowNum = 0;
	rowNum = getFunc(func, begin, flen);
	if(-1 != rowNum)  //�ҵ��˺���
	{
		string funcAllName[255] = {""};
		int returnType[255] = {-1};
		int fnlen = getFuncName(funcAllName, returnType);
		int slen = 0;
		string single[255] = {""};
		string haveFuncName = "";
		int reType = -1;
		for(int i=0; i<flen; i++)  // ��������ÿ��ֱ����
		{
			slen = covertCmd(func[i], single);
			haveFuncName = isHave(funcAllName, fnlen, single, slen);
			if("" != haveFuncName) // �жϸþ�����û�к�����
			{
				//�к����������жϸú����Ƿ����˷���ֵ
				reType = getFuncType(haveFuncName); // �õ��ú�����ֵ����
				if(1 == reType)  //���䲻Ϊvoidʱ
				{
					if(haveFuncName == single[0])  //���ַ���ֵ���ã�û��(void)
					{
						errNum[errLen] = (rowNum-flen+i+1);
						errType[errLen] = 5;
						errLen++;
					}
				}
			}
		}
		return rowNum;
	}
	else
		return -1;
}

//���ܣ����ݺ������õ�ָ����������ֵ���ͣ�0��void 1:����
//����ֵ��0��1, -1����������
int getFuncType(string funcName)
{
	int fnlen = 0;  //�����ܸ���
	string funcAllName[255] = {""};
	int returnType[255] = {-1};

	fnlen = getFuncName(funcAllName, returnType);

	for(int i=0; i<fnlen; i++)
	{
		if(funcName == funcAllName[i])
		{
			return returnType[i];
		}
	}
	return -1;
}

//���ܣ��ж�cmp����û����std�е�Ԫ��
//������len1 std���ȣ�len2 cmp����
//����ֵ��cmp����std�����ȳ��ֵ��ַ���,û�еĻ����ؿ��ַ���
string isHave(string std[], int len1, string cmp[], int len2)
{
	int i, j;

	for(i=0; i<len2; i++)
	{
		for(j=0; j<len1; j++)
		{
			if(cmp[i] == std[j])
			{
				return cmp[i];
			}
		}
	}
	return "";
}


//���ܣ��жϳ���malloc�����ĵط��Ƿ��������䷵��ֵ
void useReturnOfMalloc()
{
	string temp = "";
	string single[255] = {""};
	int slen = 0;
	for(int i=0; i<cmdCount; i++)
	{
		temp = command[i];
		slen = covertCmd(temp,single);
		if(isIn("malloc", single, slen))  //����mallocû�У���void���������δʹ�÷���ֵ
		{
			if(!isIn("=", single, slen))
			{
				if(!isIn("void", single, slen))
				{
					errNum[errLen] = i+1;
					errType[errLen] = 5;
					errLen++;
				}
			}
		}
	}
}