#include"SeedCup.h"

//全局变量
list <db> all_db;  //存放全部的数据库
list <db>::iterator iter_current_db; // 指示正在使用（USE）的数据库
int gram = -1;
bool isUse = false;
bool divider = false;

// main 函数
int main(int argc, char **argv)
{
	 // 保存cout流缓冲区指针
	streambuf* coutBuf = cout.rdbuf();
	string output = argv[2];
	ofstream of(output);
	
	// 获取文件out.txt流缓冲区指针
	streambuf* fileBuf = of.rdbuf();
	// 设置cout流缓冲区指针为out.txt的流缓冲区指针
	cout.rdbuf(fileBuf);

/*********************************************************/

	string input = argv[1];
	//string input = "input.txt";
	execute_file(input);


/********************************************************/

	of.flush();
	of.close();
 
     // 恢复cout原来的流缓冲区指针
    cout.rdbuf(coutBuf);
	return 0;
}