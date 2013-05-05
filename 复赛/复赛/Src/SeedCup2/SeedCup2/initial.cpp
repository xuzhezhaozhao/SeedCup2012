#include"SeedCup2.h"

//���ܣ���ȡ���ȫ�ֱ���������ע����Ϊ��
void initial(string inputFile)
{
	 readFile(inputFile);   // ��ȡ�ı��е�����
	 delAnnotation();   // ɾ��ע��
	 delCmdString();		//ɾ��������˫����֮�������
}

//���ܣ���ȡָ���ļ���ÿ�е�ȫ�ֱ���command[]�б��棬����Ҳ�㣬cmdCount�б���������������
void readFile(string inputFile)
{	
	cmdCount = 0;
	char temp[255] = "";  // ���һ������

	ifstream fin(inputFile, ifstream::in);   // ���ļ�
	while(!fin.eof())
	{
		fin.getline(temp,254,'\n');   // ����һ�����temp���Ի��з��ָ�
		command[cmdCount] = temp;
		cmdCount++;
	}

	fin.close();   // �ر��ļ�
}

//���ܣ�ɾ��ע��, ����ɾ���м�ע�ͣ���ע����Ϊ��
void delAnnotation()
{
	int i, j, k;
	int pose_begin, pose_end;
	for(i = 0; i<cmdCount; i++)
	{
		pose_begin = command[i].find("/*");
		if(pose_begin != -1)
		{
			for( j=i; j<cmdCount; j++)
			{
				pose_end = command[j].find("*/");
				if(pose_end != -1)
				{
					for( k = i+1; k < j; k++)
					{
						command[k] = "";
					}
					if(i == j)
					{
						command[i] = command[i].substr(0, pose_begin)
							+command[i].substr(pose_end + 2, command[i].size() - pose_end -2);
					}
					else
					{
						command[i] = command[i].substr(0, pose_begin);
						command[j] = command[j].substr(pose_end + 2,command[j].size() - pose_end -2);
					}
					break;
				}
			}
		}
	}
}

//���ܣ����滻, �����������Ͳ������������
void macroReplace()
{
	macroSimpleReplace();
	macroComplexReplace();
}

//���ܣ����������ĺ��滻��#define MAX (100*100)
void macroSimpleReplace()
{
	int i, j, k;
	string macroName = "";
	string macroValue = "";

	int pos[10] = {-1};
	int posCount = -1;

	string temp = "";
	string single[255] = {""};
	int slen = 0;
	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		slen = getSingle(temp, single);
		if("#define" == single[0] && 3 == slen) // ���� #define MAX (100*100)
		{
			macroName = single[1];
			macroValue = single[2];

			for(j=i+1; j<cmdCount; j++)
			{
				temp = command[j];
				slen = covertCmd(temp, single);
				posCount = isContain(macroName, single, slen, pos);
				if(-1 != posCount) // ˵�����к꣬Ҫ�滻
				{
					for(k=0; k<posCount; k++)
					{
						single[pos[k]] = " " + macroValue + " ";
					}
					command[j] = "";
					//���滻����ַ���ƴ����������
					for(k=0; k<slen; k++)
					{
						single[k] = " " + single[k] + " ";
						command[j] = command[j] + single[k];
					}
				}
			}
		}
	}
}

//���ܣ��������ĺ��滻
void macroComplexReplace()
{
	int i, j;
	string macroName = "";
	string macroValue = "";

	int pos[10] = {-1};
	int posCount = -1;

	string temp = "";
	string single[255] = {""};
	int slen = 0;
	string macroDef = "";
	for(i=0; i<cmdCount; i++)
	{
		temp = command[i];
		if(isComplexMacroDef(temp))  // ���κ궨��
		{
			macroDef = command[i];
			slen = covertCmd(temp, single);
			macroName = single[1];  // �õ��������ĺ���
			for(j=i+1; j<cmdCount; j++)
			{
				temp = command[j];
				slen = covertCmd(temp, single);;
				if(isIn(macroName, single, slen))   // ���õ��˸ú�
				{
					command[j] = singleComplexMacroReplace(macroDef, command[j]);
					j--; // �滻һ������ټ��һ�¸���
				}
			}
		}
	}
}

//���ܣ��õ��������ĺ�Ĳ����������䱣����macroVarName������
//������macro �궨�����
//����ֵ����������
int getMacroVarName(string macro, string macroVarName[])
{
	int i;
	int macroVarLen = 0;
	string single[255] = {""};
	int slen = 0;
	slen = covertCmd(macro, single);

	for(i=3; i<slen; i++)
	{
		if(")" != single[i])   // ˵��û�е�����������λ��
		{
			if("," != single[i])   // �������ڲ��Ƕ��ž��ǲ�����
			{
				macroVarName[macroVarLen] = single[i]; // ������������������
				macroVarLen++;
			}
		}
		else
		{
			break;
		}
	}

	return macroVarLen;
}

//���ܣ��ж�һ������Ƿ��Ǵ������ĺ궨�����
//����ֵ���Ƿ���true
bool isComplexMacroDef(string test)
{
	string single[255] = {""};
	int slen = 0;
	string tempSingle[255] = {""};
	int templen = 0;
	slen = getSingle(test, single);

	if("#define" == single[0]) // ���� #define MAX(a, b) ((a)*(b))
	{
		templen = covertCmd(single[1], tempSingle);  // �����εĺ��ɢ
		if(isIn("(", tempSingle, templen))   // �������ţ�˵������һ�����εĺ�Ķ���
		{
			return true;
		}
	}
	return false;
}

//���ܣ���#define MAX(a, b) ((a)*(b))  �õ�((a)*(b)) ��ɢ����ַ�������
//������macro �궨�����
//����ֵ�����鳤��
int getComplexMacroValue(string macro, string complexMacroValue[])
{
	int complexMacroValueLen = 0;
	string single[255] = {""};
	int slen = 0;
	slen = covertCmd(macro, single);
	for(int i=0; i<slen; i++)
	{
		if(")" == single[i])   // i֮��ľͺ�ֵ
		{
			for(int j=i+1; j<slen; j++)
			{
				complexMacroValue[complexMacroValueLen] = single[j];
				complexMacroValueLen++;
			}
			break;
		}
	}
	return complexMacroValueLen;
}


//���ܣ��õ�ʹ�ô��εĺ��еĴ��ݵ�ֵ����MAX(2, (3)) �е�2��(3)��ֻ�õ���һ���þ��м�⵽�ĺ�
//������macroName ������ useMacro ���øú����䣬macroVarLen ��θ���
//����ֵ�����ؽ����õĺ��ɢ����ַ�������ĳ���
int getComplexMacroRealValue(string macroName, string useMacro, int macroVarLen, string macroRealValue[])
{
	string useSingle[255] = {""};  // ���ú�����
	int useLen = 0;

	useLen = covertCmd(useMacro, useSingle);   // �����ú�����ɢ

	int posCount = -1;  // ������е��øú�Ĵ���
	int pos[10] = {-1};   // ���õ�λ��

	posCount = isContain(macroName, useSingle, useLen, pos);  // �õ����ú��λ��

	int realValueLen = 0;  //���ݲ������鳤��
	int j;

	//�������ҵ���������ų��ֵ�λ��
	int littleBracket = 0; // ���С����ƥ���־
	int rightMacro = 0; // �����ҵ���λ��

	for(int i=pos[0]+1; i<useLen; i++) // �Ӻ��������λ�ÿ�ʼƥ��
	{                      
		if("(" == useSingle[i])
		{
			littleBracket++;
		}
		if(")" == useSingle[i])
		{
			littleBracket--;
		}
		if(0 == littleBracket && i != pos[0]+1)
		{
			rightMacro = i;
		}
	}

	//��ʼ��ȡ���ݵĲ��� MAX(a, (b))
	for(int i=pos[0]+2; i<useLen; i++)
	{
		j = i;
		if(0 != macroVarLen)  // ������β�
		{
			while("," != useSingle[j] && j != rightMacro) // ��Ϊ����˵������һ�����ݲ���, û�е����������˵����Ҫ����
			{
				if(j != rightMacro)  // û�е����β// if(MAX(2, 3))
				{
					macroRealValue[realValueLen] = macroRealValue[realValueLen] + useSingle[j];	
					j++;
				}
				else
				{
					break;   //�����β������
				}
			}
			realValueLen++;
			
			if(j == rightMacro)  // ���˺��������λ��
				break;

			i=j;   // iƫ�Ƶ�����λ��
		}
	}
	int temp = rightMacro-pos[0]+1;
	return temp;
}


//���ܣ�չ�����������˴������ĺ�����, ֻչ����һ���þ��м�⵽�ĺ�
//������macroDef �궨����䣬 useMacro ������䣬
//����ֵ������չ��������
string singleComplexMacroReplace(string macroDef, string useMacro)
{
	int i, j;
	// �õ��������
	int macroVarNameLen = 0;
	string macroVarName[255] = {""};
	macroVarNameLen = getMacroVarName(macroDef, macroVarName); 


	// ��#define MAX(a, b) ((a)*(b))  �õ�((a)*(b)) ��ɢ����ַ�������
	int macroValueLen = 0;
	string complexMacroValue[255] = {""};
	macroValueLen = getComplexMacroValue(macroDef, complexMacroValue);  
	
	//�õ�ʹ�ô��εĺ��еĴ��ݵ�ֵ����MAX(2, (3)) �е�2��(3)
	string single[255] = {""};

	covertCmd(macroDef, single);
	string macroName = single[1];
	string macroRealValue[255] = {""}; 
	int useMacroLen = 0;

	useMacroLen = getComplexMacroRealValue(macroName, useMacro, macroVarNameLen, macroRealValue);

	//չ����
	for(i=0; i<macroVarNameLen; i++)  //��α���
	{
		for(j=0; j<macroValueLen; j++)  //��ֵ��ɢ����������
		{
			if(macroVarName[i] == complexMacroValue[j]) // ��γ��֣���ʹ���ֵ����
			{
				complexMacroValue[j] = macroRealValue[i];   
			}
		}
	}

	//��չ����ĺ�����һ���ַ���
	string replacedMacro = "";
	for(i=0; i<macroValueLen; i++)
	{
		replacedMacro += complexMacroValue[i];
	}
	
	//�ҵ����ڸþ��е�һ�γ��ֵ�λ��
	string temp = useMacro;
	int slen = covertCmd(temp, single);

	int pos[10] = {-1};
	int posCount = -1;
	posCount = isContain(macroName, single, slen, pos);
	if(-1 != posCount)
	{
		for(i=pos[0]; i<pos[0]+useMacroLen; i++)
		{
			single[i] = "";   //��ԭ�궼��Ϊ��
		}
		single[pos[0]] = " " + replacedMacro + " ";  // ʵ�ֺ��滻
	}

	// ���滻������������
	string replacedUseMacro = "";
	for(i=0; i<slen; i++)
	{
		single[i] = " " + single[i] + " ";
		replacedUseMacro += single[i];
	}

	return replacedUseMacro;
}


//���ܣ�ɾ���ַ�����˫����֮������, ����˫����
void delString(string & str)
{
	int pose1,pose2;
	pose1 = str.find("\"");
	while(pose1 != -1)
	{
		pose2 = str.find("\"",pose1+1);
		if(pose2 != -1)
		{
			str.erase(pose1+1, pose2-pose1-1);
		}
		pose1 = str.find("\"", pose2);
	}
}

//���ܣ�ɾ����ȡ���Ĵ����е�˫����֮�������
void delCmdString()
{
	int i;
	for(i=0; i<cmdCount; i++)
	{
		delString(command[i]);
	}
}