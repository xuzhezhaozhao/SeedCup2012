/* ʵ��5.2���ܣ�ָ���� */

#include"SeedCup2.h"

//���ܣ������к������й�ռ��
void assignNull()
{
	int begin = 0;
	while(-1 != begin)
	{
		begin = funcAssignNull(begin);
	}
}


//���ܣ�������beginλ�ú�ĵ�һ���������й�ռ��
//����ֵ�����غ�����β����һ���кż�1��ֵ����1��ʾû���ҵ�������
int funcAssignNull(int begin)
{
	int i;
	string func[255] = {""};  // ���溯����
	string single[255] = {""};  // ��ɢ����ַ���
	int flen = 0; //�������� 
	int slen = 0; 
	int rowNum = 0;  // �кţ���0Ϊ��ʼ
	rowNum = getFunc(func, begin, flen);  // ���������е���һ������1
	if(-1 != rowNum)
	{
		for(i=0; i<flen; i++)
		{
			slen = covertCmd(func[i], single);

			int posCount = 0;
			int pos[10] = {-1};
			
			string check_p = "";

			posCount = isContain("free", single, slen, pos);

			if(-1 != posCount) // ˵���ں�����i�У�0��ʼ������"free��������"
			{
				check_p = single[pos[0]+2];  // ��ָ������check_p
				if(!checkNull(func, flen, i, check_p))  //���֮��û�й�ջ���ʹ��
				{
					errNum[errLen] = (rowNum-flen+i+1);
					errType[errLen] = 2;
					errLen++;
		//			cout << "line=" << errNum[errLen-1] << ",error=2" << endl; // for debug
				}
					
			}

		}

		return rowNum;
	}

	else
		return -1;
}

//���ܣ�����ں���func��pos��λ�ó��ֵ�free(check_p),��ô�ڸú����������ڴ�pos+1�п�ʼ���, �������û�й�վ���
//+����������򱨴�һֱû�г���check_p = NULL����Ҳ����
//������func[] ���溯���е����飬 flen ���������鳤�ȣ� pos ����free��λ�ã���Ժ������飩��check_p free��ָ��
//����ֵ��true ��ʾ�й�ղ���
bool checkNull(string func[], int flen, int pos, string check_p)
{
	int i = 0;
	int slen = 0;
	string single[255] = {""};
	for(i=pos+1; i<flen; i++)
	{
		slen = covertCmd(func[i], single);

		int posCount = 0;
		int pos[10] = {-1};
		
		posCount = isContain(check_p, single, slen, pos);

		if((-1 != posCount)) // ˵�������õ��˸�ָ�룬����������Ƿ��ǽ����յĲ���
		{
			if(("=" == single[pos[0]+1] && "NULL" == single[pos[0]+2]))   // check_p = NULL
				return true;
			else  // ������ǹ�ղ�����Ҫ����
			{
				if(";" != single[pos[0]+1])    // �������check_p;
					return false;
			}
		}
	}

	return false;
}