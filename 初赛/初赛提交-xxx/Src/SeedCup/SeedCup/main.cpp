#include"SeedCup.h"

//ȫ�ֱ���
list <db> all_db;  //���ȫ�������ݿ�
list <db>::iterator iter_current_db; // ָʾ����ʹ�ã�USE�������ݿ�
int gram = -1;
bool isUse = false;
bool divider = false;

// main ����
int main(int argc, char **argv)
{
	 // ����cout��������ָ��
	streambuf* coutBuf = cout.rdbuf();
	string output = argv[2];
	ofstream of(output);
	
	// ��ȡ�ļ�out.txt��������ָ��
	streambuf* fileBuf = of.rdbuf();
	// ����cout��������ָ��Ϊout.txt����������ָ��
	cout.rdbuf(fileBuf);

/*********************************************************/

	string input = argv[1];
	//string input = "input.txt";
	execute_file(input);


/********************************************************/

	of.flush();
	of.close();
 
     // �ָ�coutԭ������������ָ��
    cout.rdbuf(coutBuf);
	return 0;
}