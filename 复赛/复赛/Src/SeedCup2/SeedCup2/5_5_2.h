/* ʵ��5.5.2�Ĺ��ܣ�δʹ�õ���Դ֮���� */

#ifndef _5_5_2_H_
#define _5_5_2_H_

using namespace std;

//���ܣ��������ú�
void uselessMacro();

//���ܣ��õ��궨������еĺ���
//����ֵ������
string getMacroName(string test);

//���ܣ��õ�һ�������ļ���ʹ�õĴ���, "MAX;"�� ��"MAX, 1"��"2, MAX, 1;"������ʹ���˺�
//����ֵ������
int getMacroCount(string test);

#endif