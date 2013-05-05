/* 实现自定义的功能: 
	1、检测内存是否泄漏，即用malloc开了内存，没有free这块内存。
*/

#ifndef _5_7_1_CUSTOM_H_
#define _5_7_1_CUSTOM_H_

using namespace std;

/*
功能：检测内存泄漏的情况
考虑到的情况：有指针指向该内存，没有free, malloc时无指针指向
*/
void memoryLeak();

//功能：检测一个函数中的内存泄漏问题
int memoryLeakFunc(int begin);

//功能：检测一个函数中的内存泄漏问题
int memoryLeakFunc1(int begin);

//功能：检测一个函数中的内存泄漏问题 1.2、用指针指向malloc开的内存，在没有释放这块内存之前改变了该的指针的值，使该块内存无法释放.
//改变值的形式有指针－指针，指针－数组名，指针－变量取址（&）
int memoryLeakFunc2(int begin);

//功能：得到函数中所有的指针变量名，包括数组名
//返回值：数组长度
int getPointName(string func[], int flen, string pointName[]);

//功能：得到全局变量中开了内存的指针名
//返回值：数组长度
int getGloberMalloc(string globeMallocName[]);

//功能：得到全局变量中的指针变量名，数组变量名
//返回值：数组长度
int getGloblePointName(string globePointName[]);

//功能：检查全局变量开的内存是否释放，不考虑局部变量覆盖的影响
void memLeakGlober();

#endif