#include"SeedCup2.h"

//ȫ�ֱ���
string command[1000] = {""};  // �������������ڸ�������
int cmdCount = 0;        // ��¼�������������
int errNum[255] = {-1};		//��¼������к�
int errType[255] = {-1};    //���к����Ӧ�Ĵ��������
int errLen = 0;				//����ĸ���

/* main ���� */
int main(int argc, char **argv)
{
/*
	streambuf* coutBuf = cout.rdbuf(); // ����cout��������ָ��
	string input = argv[1];
	initial(input);
	string output = "";

	if(3 == argc)   // û��-c����ʱ
	{
		output = argv[2];
	} 
	else   // ���в���ʱ
	{
		output = argv[3];	
	}

	ofstream of(output);
	streambuf* fileBuf = of.rdbuf(); // ��ȡ�ļ�out.txt��������ָ��
	cout.rdbuf(fileBuf);  // ����cout��������ָ��Ϊout.txt����������ָ��

	if(3 == argc)   // û��-c,-x����ʱ, ���� displayError();
	{
		displayError();
	}
	if(4 == argc && 0 == strcmp("-c", argv[2]))   // ���У�c����ʱ ���� getGraphic(step);
	{
		macroReplace();    // �Ƚ��к��滻
		string step[100][100] = {""};
		getGraphic(step);
	}
	if(4 == argc && 0 == strcmp("-x", argv[2])) // ���У�x����ʱ ���� displayCustomError();
	{
		displayCustomError();
	}

	of.flush();
	of.close();    
    cout.rdbuf(coutBuf); // �ָ�coutԭ������������ָ��
*/

	string input = "input.c";
	initial(input);

/******    ������     ******/

	//displayError();   // ��ӡ�������

	//displayCustomError();   // ��ӡ�Զ������

/******	 ��ӡ��������ͼ  *****/

	macroReplace();    // �Ƚ��к��滻
	string step[100][100] = {""};
	getGraphic(step);

/*****      TEST       ****/

	return 0;
}