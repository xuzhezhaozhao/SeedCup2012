#include"SeedCup2.h"


// ���ܣ�����һ�����������йص������д�command[]��ȡ�������뵽func�����У�
//+ ��command[]��beginλ��(0��ʼ)��ʼ���Һ�����ֻ�����ҵ��ĵ�һ������������main����
//+ �� void func(){int i=1;
//+			int j=8;
//+		}  
//+ ���䰴�д���func[]��,�������ԭʼ���û�о�������
//����ֵ�����ض�ȡ�ĺ�����һ���кż�1��ֵ,��֮��û���ҵ������򷵻أ�1
//������begin������ʼλ�ã�func_len�Ǹú�����������
int getFunc(string func[], int begin, int & func_len)
{
	int i=0;
	int j=0;
	int k=0;
	func_len = 0;
	string single[100] = {""};
	string temp = "";
	int len = 0;
	int bracket = 0;  // ������ƥ����

	for(i=begin; i<cmdCount; i++)
	{
		temp = command[i];
		len = covertCmd(temp, single);

		if(isFuncDef(single, len)) // �ж��Ƿ��Ǻ�������Ŀ�ʼ
		{
			// �Ǻ����Ŀ�ʼ��������ɺ��Ҫbreak��ѭ��
			bracket = 0;  //������ƥ��ֵ��ʼΪ0
			j = 0;
			for(k=i; k<cmdCount; k++)
			{
				func[j] = command[k];   // �Ƚ����и���func[j]
				func_len = j+1;
				j++;
				temp = command[k];
				len = covertCmd(temp, single);

				if(k == i && "}" == single[len-1])
				{
					return (k+1);
				}
				else
				{
					getBracket(single, len, bracket); // �õ�������ƥ�����

					if(k!=i && 0 == bracket)   // ������ƥ����ɣ�˵�������������
					{
						return (k+1);
					}
					else // û��ƥ�������˵���������廹û�н���
					{
						continue;
					}
				}
			}
		}
	}

	return -1;
}


//���ܣ���ȡָ���������ĺ���
void getFuncFromName(string func[], int & func_len, string funcName)
{
	int funcPos = getFuncPosFromName(funcName);
	if(-1 != funcPos)
	{
		(void)getFunc(func, funcPos, func_len);
	}
}

// ���ܣ���#define����ĺ������δ浽def������,��#define MAX 100, ��MAX����def
// ���أ����غ����
int getDefine(string def[])
{
	int i=0;

	string temp = "";
	string single[255] = {""};
	int len = 0;

	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		single[0] = "";
		covertCmd(temp, single);
		
		if("#define" == single[0])
		{
			def[len] = single[1];
			len++;
		}
	}
	return len;
}

//���ܣ��õ������еı������������β���
//������������begin������ʼλ�ã�ֻ�����ҵ��ĵ�һ������
//����ֵ����������
int getFuncVar(string funcVar[], int begin)
{
	int len = 0;  //�������鳤��
	int flen = 0; // �����ܵ�����
	int i;
	string func[255] = {""};
	getFunc(func, begin, flen);
	for(i=0; i<flen; i++)
	{
		getVar(func[i], funcVar, len);
	}
	return len;
}

//���ܣ���һ�������������(������const,sttic,signed,unsigned,extern��ͷ)�еı���������funVar[len]��len��ԭ�е����鳤�ȣ��������Ա���ԭ���ı���,
//+���ܵõ������������β����� ��int const**i, j, k, m;
void getVar1(string single[], int slen, string funcVar[], int & len)
{
	int i=0;
	if(isType(single[0]))
	{
		//�õ����������� int i;  int *p; int **p; int & s; ��const
		if("(" != single[2])   
		{
			if("*" != single[1] && "**" != single[1] && "&" != single[1])  // int i;int const i;int const* i;
			{
				if("const" != single[1]) // int i;
				{
					funcVar[len] = single[1];
					len++;
			
					for(i=2; i<slen; i++) // ���int i=0, j;�������
					{
						if("," == single[i])
						{
							funcVar[len] = single[i+1];
							len++;
						}
					}
				}  
				else if ("const" == single[1] && "*" != single[2] && "**" != single[2])
				{
					funcVar[len] = single[2];
					len++;
			
					for(i=3; i<slen; i++) // ���int const i=0, j;�������
					{
						if("," == single[i])
						{
							funcVar[len] = single[i+1];
							len++;
						}
					}
				}  // int const* i;int const ** i;
				else if("const" == single[1] && ("*" == single[2] || "**" == single[2]) )
				{
					funcVar[len] = single[3];
					len++;
			
					for(i=4; i<slen; i++) // ���int const i=0, j;�������
					{
						if("," == single[i])
						{
							funcVar[len] = single[i+1];
							len++;
						}
					}
				}		
				else
				{
					;
				}
			}
			else   //int * i; int *const i; int & i;
			{
				if("const" != single[2])  // int * i; int & i;
				{
					funcVar[len] = single[2];
					len++;
					for(i=3; i<slen; i++) // ���int* i=0, j;�������
					{
						if("," == single[i])
						{
							funcVar[len] = single[i+1];
							len++;
						}
					}
				}
				else
				{
					funcVar[len] = single[3];
					len++;
					for(i=4; i<slen; i++) // ���int* const i=0, j; int const *i, j;�������
					{
						if("," == single[i])
						{
							funcVar[len] = single[i+1];
							len++;
						}
					}
				}
			}
		}
	}
	funcVar[len] = "";
}

//���ܣ�����getVar1,����������ʶ��signed �� unsigned
void getVar2(string single[], int slen, string funcVar[], int & len)
{
	int i, j;
	string temp[255] = {""};
	if("signed" == single[0] || "unsigned" == single[0])
	{
		j = 0;
		for(i=1; i<slen; i++)
		{
			temp[j] = single[i];
			j++;
		}	
		getVar1(temp, slen-1, funcVar, len);
	}
	else
	{
		getVar1(single, slen, funcVar, len);
	}
}

//���ܣ�����getVar2,�������������������ʶ��const��ͷ��
void getVar3(string single[], int slen, string funcVar[], int & len)
{
	int i, j;
	string temp[255] = {""};
	if("const" == single[0])
	{
		j = 0;
		for(i=1; i<slen; i++)
		{
			temp[j] = single[i];
			j++;
		}
		getVar2(temp, slen-1, funcVar, len);
	}
	else
	{
		getVar2(single, slen, funcVar, len);
	}
}

//���ܣ�����getVar3,�������������������ʶ��extern��static��ͷ��
void getVar4(string single[], int slen, string funcVar[], int & len)
{
	int i, j;
	string temp[255] = {""};
	if("extern" == single[0] || "static" == single[0])
	{
		j = 0;
		for(i=1; i<slen; i++)
		{
			temp[j] = single[i];
			j++;
		}
		getVar3(temp, slen-1, funcVar, len);
	}
	else
	{
		getVar3(single, slen, funcVar, len);
	}
}

//���ܣ���getVar2()�������ƣ��������������������ʶ�������������β�����������ֵ���Ͳ�����const,[un]singed,extern,static���� void func(signed int const* p1, float *const p2)
void getVar5(string single[], int slen, string funcVar[], int & len)
{
	string temp[20][255] = {""};
	int tlen[20] = {0};
	int i, j, k;

	i = 0;
	j = 0;
	k = 0;
	if(isFuncDef(single, slen))
	{			
		if("void" != single[3]) // void func(void)
		{
			for(i=3; i<slen; i++)
			{
				k=0;
				while("," != single[i] && (slen-1) != i)
				{
					temp[j][k] = single[i];
					tlen[j]++;
					k++;
					i++;
				}
				j++;
			}
		}

		for(i=0; i<j; i++)
		{
			getVar4(temp[i], tlen[i], funcVar, len);
		}
	}
}

//���ܣ���getVar5()�������ƣ�������������������˷���ֵ���Ͱ���const,[un]singed,extern,static���� static void func(signed int const* p1, float *const p2)
void getVar6(string single[], int slen, string funcVar[], int & len)
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
		getVar5(temp, slen-1, funcVar, len);
	}
	else
	{
		getVar5(single, slen, funcVar, len);
	}
}

//���ܣ��ۺ�getVar��������һ�������ж���Ĳ�����
void getVar(string cmd, string funcVar[], int & len)
{
	string single[255] = {""};

	int slen;
	slen = covertCmd(cmd, single);

	getVar4(single, slen, funcVar, len);
	getVar6(single, slen, funcVar, len);
}

//���ܣ��õ�ȫ�ֱ�����
//����ֵ��ȫ�ֱ������鳤��
int getGlobeVar(string globeVar[])
{
	int i=0;
	string temp = "";
	string single[255] = {""};
	int slen = 0;

	int glen = 0; //ȫ�ֱ������鳤��
	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		slen = covertCmd(temp, single);
		if(!isFuncDef(single, slen))   // ������һ����������˵��֮��û��ȫ�ֱ�����������
		{
			getVar(temp, globeVar, glen);
		}
		else
		{
			break;
		}
	}
	return glen;
}


//���ܣ��õ�ȫ���ĺ���������Ӧ�ķ���ֵ���ͣ�0��ʾvoid,1��ʾ����������main����
//����ֵ�����鳤��
int getFuncName(string funcName[], int returnType[])
{
	string single[255] = {""};
	int slen = 0;
	string temp = "";
	int nlen = 0;
	for(int i=0; i<cmdCount; i++)
	{
		temp = command[i];
		slen = covertCmd(temp, single);
		if(isFuncDef(single, slen))   // ����Ǻ������壬ֻ�ж����˵ĺ������ܱ�����
		{
			funcName[nlen] =  getFuncStaName(single, slen, returnType[nlen]);
			nlen++;
		}
	}

	//���ָ����ϵͳ����
	funcName[nlen] = "malloc";
	returnType[nlen] = 0;   // !!! ע�⣺����malloc��ֵӦ��Ϊ1������Ϊ"��*int��malloc();"���������,����дһ����һ���������malloc����ֵ
 	nlen++;
	funcName[nlen] = "free";
	returnType[nlen] = 0;
	nlen++;
	funcName[nlen] = "getchar";
	returnType[nlen] = 1;
	nlen++;

	return nlen;
}

//���ܣ��õ�������������к�����������ֵ����
string getFuncStaName(string single[], int slen, int & returnType)
{
	returnType = 1;
	int i=0;
	while("(" != single[i])
	{
		if("void" == single[i])
		{
			returnType = 0;
		}
		i++;
	}

	return single[i-1];
}


//���ܣ��õ�ָ�����������λ��(0��ʼ)
//����ֵ��λ�ã������ڷ��أ�1
int getFuncPosFromName(string funcName)
{
	int i = 0;
	string temp = "";
	string single[255] = {""};
	int slen = 0;
	int tempType = 0;
	string tempName = "";
	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		slen = covertCmd(temp, single);
		if(isFuncDef(single, slen))
		{
			tempName = getFuncStaName(single, slen, tempType);
			if(tempName == funcName)
			{
				return i;
			}
		}
	}
	return -1;
}

//���ܣ��ж�cmp����û����std�е�Ԫ�أ��еĻ�׷�Ӵ���get������
//������len1 std���ȣ�len2 cmp����, len3 get����
void haveGet(string std[], int len1, string cmp[], int len2, string get[], int & len3)
{
	int i, j;

	for(i=0; i<len2; i++)
	{
		for(j=0; j<len1; j++)
		{
			if(cmp[i] == std[j])
			{
				get[len3] = cmp[i];
				len3++;
			}
		}
	}
}