/* ʵ��5.3.3���ܣ���Ч��֧֮switch���*/

#ifndef _5_3_3_H_
#define _5_3_3_H_

using namespace std;

//���ܣ������Ч��switch��֧
void switchErr();

//���ܣ��õ�һ�������еĴ�ָ��λ�ò��ҵ���һ��switch�����������������������
//������begin�ǴӺ����ĵڼ��п�ʼ���ң�switchLen��switch���ĳ���
//����ֵ���������switch��β��һ�м�1
int getOneSwitch(string func[], int flen, int begin, string switchCmd[], int & switchLen);

//���ܣ���һ�������м����Ч��switch���
//����ֵ�����غ�����β��һ�м�1
int switchInfunc(int beginFunc);

#endif