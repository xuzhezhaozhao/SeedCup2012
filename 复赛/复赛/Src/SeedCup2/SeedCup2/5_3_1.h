/* ʵ��5.3.1���ܣ���Ч��֧֮if��� */

#ifndef _5_3_1_H_
#define _5_3_1_H_

using namespace std;

//�����Ч��while��֧
void ifErr();

//���һ�����ʽΪtrue��false
void if1();

//����������ʽΪ����������ʽ ��"-1+(2*3/5)", �����д���С����
void if2();

//����������ʽ��ֻ��һ�����������Ҹñ�����ֵ��֮ǰ��ֵΪ��ֵ��
void if3();

//���ܣ������������һ�������е����
int ifFunc3(int begin);

//���ܣ��õ�һ������еı�����,���浽������
//������beginָ�������￪ʼ���Һ���
//����ֵ���������ĸ���
int getVarFromOneCmd(int begin, string cmd, string oneCmdVarName[]);
#endif