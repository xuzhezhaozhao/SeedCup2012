/* ʵ��5.6�Ĺ���: ������ϵ����ͼ(�򵥼��ݹ�) */

#ifndef _5_6_H_
#define _5_6_H_

using namespace std;
/*
���ܣ����ݵ������ó��Ķ�άͼ��Ҫ��ĸ�ʽ��ӡ����������ͼ
*/
void getGraphic(string step[][100]);

/*
���ܣ���һ���������ȵõ�ָ����������(������main����)�ĵ��ù�ϵ, ������ʽ, ��ʾf1����f2��f3, ���������һ����ά����step1[][100](�ж��ٵ��ú������ж�����)��
f1 f2
#  f3
����ֵ����ά���������������ú�������
*/
int graphStep1(string funcName, string step1[][100]);

/*
���ܣ��ڶ������õ�main�����ĵ��ù�ϵ, ��main������ά��Ӧ�ø��󣬶���Ϊ100*100�ģ���ʼ��Ϊ��
����ֵ����ά���������������ú�������
*/
int graphStep2(string funcName, string step1[][100]);

/*
���ܣ�������, ���������������Ķ�ά��������ͼ������"#"����10��"-","*"��ʾ�գ���־�ݹ�Ľ���
����ֵ����άͼ������
*/
int graphStep3(string step3[][100]);


//���ܣ��õ�ָ���������õĺ���������������������������funcName������
//����ֵ�����鳤��
int getFuncName(string funcName[], string thisFuncName);

//���ܣ��õ�һ������еĺ�����, ���׷�Ӵ���funcNameFromCmd[]��, len������֮ǰ�ĳ���
void getFuncNameFromCmd(string cmd, string funcNameFromCmd[], int & len);

//���ܣ�ȥ���ַ����������ظ����ַ���,��������clean[]��
//������len��test[]����
//���أ�clean����
int delRepeat(string test[], int len, string clean[]);

//���ܣ���ָ����string���������򣬳���Ϊlen
void sortStringIncr(string str[], int len);

//���ܣ��ж�ָ�������Ƿ��������������
//����ֵ�������˷���true, û�е��÷���false
bool isInvokeFunc(string funcName);

//���ܣ��õ�main������ά��ͼ��row�У�0��ʼ��δβԪ�ص�ֵ
//����ֵ��δβ�ַ���
string getMainEdge(int row, string step[][100]);

//���ܣ��õ�main������ά��ͼ��row�У�0��ʼ��δβԪ�ص��кţ�0��ʼ��
//����ֵ��δβ�к�
int getMainEdgeNum(int row, string step[][100]);


//���ܣ���main��άͼδ�˲����µ��ز��ṹ
//����ֵ����άͼ����Ч����
int insertNewFunc(string step[][100], int stepLen, int row);

//���ܣ��ж���row���Ƿ�����˵ݹ�, ˼������ж��ڸ�ά�����һ���ַ����Ƿ��ǰ�����ͬ����ͬ���ǵݹ飬
//+�����ݹ�����һ���ַ����ĺ�һ���ַ�����Ϊ "*",���Խ����ݹ�
void isRecursive(string step[][100], int row);

//���ܣ���Ҫ��ת����άͼ�е��ַ�����"#"���10��"-", ���������룬"*"ת�ɿ�
void covertStep(string & str);
#endif