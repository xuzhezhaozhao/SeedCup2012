#include"SeedCup2.h"

//全局变量
string command[1000] = {""};  // 读入的命令存入在该数组中
int cmdCount = 0;        // 记录读入的命令条数
int errNum[255] = {-1};		//记录错误的行号
int errType[255] = {-1};    //与行号相对应的错误的类型
int errLen = 0;				//错误的个数

/* main 函数 */
int main(int argc, char **argv)
{
/*
	streambuf* coutBuf = cout.rdbuf(); // 保存cout流缓冲区指针
	string input = argv[1];
	initial(input);
	string output = "";

	if(3 == argc)   // 没有-c参数时
	{
		output = argv[2];
	} 
	else   // 含有参数时
	{
		output = argv[3];	
	}

	ofstream of(output);
	streambuf* fileBuf = of.rdbuf(); // 获取文件out.txt流缓冲区指针
	cout.rdbuf(fileBuf);  // 设置cout流缓冲区指针为out.txt的流缓冲区指针

	if(3 == argc)   // 没有-c,-x参数时, 调用 displayError();
	{
		displayError();
	}
	if(4 == argc && 0 == strcmp("-c", argv[2]))   // 含有－c参数时 调用 getGraphic(step);
	{
		macroReplace();    // 先进行宏替换
		string step[100][100] = {""};
		getGraphic(step);
	}
	if(4 == argc && 0 == strcmp("-x", argv[2])) // 含有－x参数时 调用 displayCustomError();
	{
		displayCustomError();
	}

	of.flush();
	of.close();    
    cout.rdbuf(coutBuf); // 恢复cout原来的流缓冲区指针
*/

	string input = "input.c";
	initial(input);

/******    检查错误     ******/

	//displayError();   // 打印常规错误

	//displayCustomError();   // 打印自定义错误

/******	 打印函数调用图  *****/

	macroReplace();    // 先进行宏替换
	string step[100][100] = {""};
	getGraphic(step);

/*****      TEST       ****/

	return 0;
}