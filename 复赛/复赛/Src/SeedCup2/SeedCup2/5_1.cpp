/* ʵ��5.1�Ĺ��ܣ���ֹ����ֵ */

#include"SeedCup2.h"

//���ܣ������к����������ֵ
void errorAssign()
{
	int begin = 0;
	while(-1 != begin)
	{
		begin = funcErrorAssign(begin);
	}
}

//���ܣ�������beginλ�ú�ĵ�һ���������д�����
//����ֵ�����غ�����β����һ���кż�1��ֵ����1��ʾû���ҵ�������
int funcErrorAssign(int begin)
{
	int i, j;
	string func[255] = {""};
	string single[255] = {""};  // ��ɢ����ַ���
	int flen = 0; //�������� 
	int slen = 0; 
	int glen = 0; // ȫ�ֱ���
	int vlen = 0; // ��������
	int rowNum = 0;  // �кţ���0Ϊ��ʼ
	rowNum = getFunc(func, begin, flen);
	if(-1 != rowNum)
	{
		string funcVar[255] = {""};  // ����������Χ�ڵı�����
		string globeVar[255] = {""}; // ȫ�ֱ�����
	
		glen =  getGlobeVar(globeVar);
		vlen = getFuncVar(funcVar, begin);

		int posCount = 0;
		int pos[10] = {-1};

		string checkVar = "";
		string rightVar = "";

		for(i=0; i<flen; i++)
		{
			slen = covertCmd(func[i], single); 
			posCount = isContain("==", single, slen, pos);
			if(-1 != posCount) // ˵������"=="
			{
				for(j=0; j<posCount; j++)
				{
					checkVar = single[pos[j]-1];
					rightVar = single[pos[j]+1];   // == �ұߵ��ַ�����Ҫ�ж��Ǳ������ǳ���
					// ����Ǳ��������ұ��ǳ����ͱ���, �������������飬��a[1][0] == 1;
					if(("]" == checkVar || isIn(checkVar, globeVar, glen) || isIn(checkVar, funcVar, vlen)) && (!isIn(rightVar, globeVar, glen) && !isIn(rightVar, funcVar, vlen)))
					{
						errNum[errLen] = (rowNum-flen+i+1);
						errType[errLen] = 1;
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


