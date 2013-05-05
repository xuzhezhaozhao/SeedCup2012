
#include"SeedCup2.h"


//功能：检查错误
void checkError()
{
	uselessMacro();  // 5_5_2  先检测无用宏
	ghostNum();      // 5_4  魔鬼数字

	macroReplace();   // 进行宏替换, 包括带参数的宏

/***  宏替换后再执行其他操作  ***/
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

//功能：按格式要求打印错误
void displayError()
{
	checkError();
	sortTwo(errNum, errType, errLen);
	for(int i=0; i<errLen; i++)
	{
		cout << "line=" << errNum[i] << ",error=" << errType[i] << endl;
	}
}


//功能：检查自定义的错误
void checkCustomError()
{
	macroReplace();
	memoryLeak();
	noInitialVar();
}

//功能：按格式要求打印自定义错误
void displayCustomError()
{
	checkCustomError();
	sortTwo(errNum, errType, errLen);
	for(int i=0; i<errLen; i++)
	{
		cout << "line=" << errNum[i] << ",error=" << errType[i] << endl;
	}
}
