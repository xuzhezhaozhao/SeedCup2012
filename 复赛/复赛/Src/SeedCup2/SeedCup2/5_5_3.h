/* ʵ��5.5.3�Ĺ��ܣ�δʹ�õ���Դ֮������ */

#ifndef _5_5_3_H_
#define _5_5_3_H_

using namespace std;

// ���δʹ�õı����������ֲ���ȫ�ֱ���
void uselessVar();


//���ܣ����ȫ�ֱ����Ƿ�ʹ��
void uselessGlobeVar();

//���ܣ����ȫ�ֱ����ں��������ʹ�ã���Ҫ���Ǿֲ�������Ӱ��
//������gfag��ʼΪ��1�������Ϊ��1,˵��ʹ�õ��˸�ȫ�ֱ���
//����ֵ��������������һ�м�1���Ҳ��������򷵻أ�1,
int isGlobeInFunc(string globeVar, int begin, int & gflag);

//���ܣ�������к�����δʹ�õı���
void uselessAllFuncVar();

//���ܣ����һ��������δʹ�õı���
//�������������ҵ���ʼλ��
//����ֵ��������������һ�м�1
int uselessFuncVar(int begin);

/*
���ܣ����һ�������ں����Ƿ��ù�, ��"int i; i;" �����Ĳ����ù�
1.�Լ�����д
2.������������ֵ
3.��Ӿ�������������ֵ. eg b = p[a]�е�a
����ֵ�����÷���true, �����򷵻�false
*/
bool isUselessFuncVar(string func[], int flen, string varName);

/*
���ܣ����һ��ȫ�ֱ����ں����Ƿ��ù�
1.�Լ�����д
2.������������ֵ
3.��Ӿ�������������ֵ. eg b = p[a]�е�a
����ֵ�����÷���true, �����򷵻�false
*/
bool isUselessGlobeVar(string func[], int flen, string varName);

//���ܣ��õ��������ں����е�һ�γ��ֵ�λ��
//����ֵ��λ�ã�0��ʼ��,�����ڷ��أ�1
int getFirstAppearPos(string func[], int flen, string varName);

//���ܣ��õ�ȫ�ֱ�������һ�γ��ֵ�λ��
//����ֵ��λ�ã�0��ʼ��,�����ڷ��أ�1
int getGolbeVarPos(string cmd[], int len, string varName);
#endif