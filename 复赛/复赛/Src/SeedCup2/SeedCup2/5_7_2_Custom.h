/* 实现自定义的功能: 
	2、检测变量是否未赋初值就使用了
		如： int i;
			 int j = i;
*/

#ifndef _5_7_2_CUSTOM_H_
#define _5_7_2_CUSTOM_H_

using namespace std;

//功能：检查所有函数的变量在使用前是否赋了初值，不检查全局变量
void noInitialVar();

//功能：检查一个函数中的变量在使用前是否赋了初值,基本思想就是检查一个变量第一次出现时其后是否是"=", 是的话就不再检查，不是的话就检查它第二次出现时其后是否是等"="
//返回值：函数结尾下一行行数减1
int noInitialVarFunc(int begin);

//功能：检查全局变量是否未赋初值就使用
void noInitialGolberVar();

#endif