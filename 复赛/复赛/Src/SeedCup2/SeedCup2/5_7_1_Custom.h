/* ʵ���Զ���Ĺ���: 
	1������ڴ��Ƿ�й©������malloc�����ڴ棬û��free����ڴ档
*/

#ifndef _5_7_1_CUSTOM_H_
#define _5_7_1_CUSTOM_H_

using namespace std;

/*
���ܣ�����ڴ�й©�����
���ǵ����������ָ��ָ����ڴ棬û��free, mallocʱ��ָ��ָ��
*/
void memoryLeak();

//���ܣ����һ�������е��ڴ�й©����
int memoryLeakFunc(int begin);

//���ܣ����һ�������е��ڴ�й©����
int memoryLeakFunc1(int begin);

//���ܣ����һ�������е��ڴ�й©���� 1.2����ָ��ָ��malloc�����ڴ棬��û���ͷ�����ڴ�֮ǰ�ı��˸õ�ָ���ֵ��ʹ�ÿ��ڴ��޷��ͷ�.
//�ı�ֵ����ʽ��ָ�룭ָ�룬ָ�룭��������ָ�룭����ȡַ��&��
int memoryLeakFunc2(int begin);

//���ܣ��õ����������е�ָ�������������������
//����ֵ�����鳤��
int getPointName(string func[], int flen, string pointName[]);

//���ܣ��õ�ȫ�ֱ����п����ڴ��ָ����
//����ֵ�����鳤��
int getGloberMalloc(string globeMallocName[]);

//���ܣ��õ�ȫ�ֱ����е�ָ������������������
//����ֵ�����鳤��
int getGloblePointName(string globePointName[]);

//���ܣ����ȫ�ֱ��������ڴ��Ƿ��ͷţ������Ǿֲ��������ǵ�Ӱ��
void memLeakGlober();

#endif