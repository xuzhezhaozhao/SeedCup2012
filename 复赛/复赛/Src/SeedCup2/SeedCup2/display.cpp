
#include"SeedCup2.h"


//���ܣ�������
void checkError()
{
	uselessMacro();  // 5_5_2  �ȼ�����ú�
	ghostNum();      // 5_4  ħ������

	macroReplace();   // ���к��滻, �����������ĺ�

/***  ���滻����ִ����������  ***/
	errorAssign();   // 5_1
	assignNull();    // 5_2
	ifErr();		 // 5_3_1
	whileErr();	     // 5_3_2
	switchErr();	 // 5_3_3
	forError();		 // 5_3_4
	uselessFunc();   // 5_5_1
	uselessVar();    // 5_5_3
	uselessReturn(); // 5_5_4
}

//���ܣ�����ʽҪ���ӡ����
void displayError()
{
	checkError();
	sortTwo(errNum, errType, errLen);
	for(int i=0; i<errLen; i++)
	{
		cout << "line=" << errNum[i] << ",error=" << errType[i] << endl;
	}
}


//���ܣ�����Զ���Ĵ���
void checkCustomError()
{
	macroReplace();
	memoryLeak();
	noInitialVar();
}

//���ܣ�����ʽҪ���ӡ�Զ������
void displayCustomError()
{
	checkCustomError();
	sortTwo(errNum, errType, errLen);
	for(int i=0; i<errLen; i++)
	{
		cout << "line=" << errNum[i] << ",error=" << errType[i] << endl;
	}
}
