/* ʵ��5.5.4�Ĺ��ܣ�δʹ�õ���Դ֮������ֵ */

#ifndef _5_5_4_H_
#define _5_5_4_H_

using namespace std;

//���ܣ����ÿһ�������ĵ��ú����Ƿ��õ���������ֵ
void uselessReturn();

//���ܣ����һ�������еĵ��ú����Ƿ��õ���������ֵ
//����ֵ������������һ�м�1��û�к����򷵻أ�1
int uselessReturnFunc(int begin);

//���ܣ����ݺ������õ�ָ����������ֵ���ͣ�0��void 1:����
//����ֵ��0��1
int getFuncType(string funcName);

//���ܣ��ж�cmp����û����std�е�Ԫ��
//������len1 std���ȣ�len2 cmp����
//����ֵ��cmp����std�����ȳ��ֵ��ַ���,û�еĻ����ؿ��ַ���
string isHave(string std[], int len1, string cmp[], int len2);

//���ܣ��жϳ���malloc�����ĵط��Ƿ��������䷵��ֵ
void useReturnOfMalloc();
#endif