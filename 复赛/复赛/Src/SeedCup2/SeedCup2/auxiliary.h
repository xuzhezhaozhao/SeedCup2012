#ifndef _AUXILIARY2_H_
#define _AUXILIARY2_H_

using namespace std;

//���ܣ��жϸ�������(�������Ѿ��������ַ�����ת����)�ǲ��Ǻ�������(��������)�Ŀ�ͷ����void main()��len���ַ����������Ч����
//����ֵ���Ƿ���true
bool isFuncDef(string str[], int len);

//���ܣ��жϸ�������(�������Ѿ��������ַ�����ת����)�ǲ��Ǻ�������(���Ƕ���)����"void myFunc();", len���ַ����������Ч����
//����ֵ���Ƿ���true
bool isFuncState1(string str[], int len);

//���ܣ��жϸ�������(�������Ѿ��������ַ�����ת����)�ǲ��Ǻ�������(���Ƕ���)������ֵ���Ͱ���const,[un]singed,extern,static����"extern void myFunc();", len���ַ����������Ч����
//����ֵ���Ƿ���true
bool isFuncState(string single[], int slen);

//������ƥ���ѯ�����single�����е����������bracketֵ��1�����Ҵ�������bracketֵ��1
void getBracket(string single[], int len, int & bracket);

//С����ƥ���ѯ�����single�����е���С������bracketֵ��1������С������bracketֵ��1
void getLittleBracket(string single[], int len, int & bracket);

//�����ַ����Ƿ����������͹ؼ���
bool isType(string test);

//���ܣ� ָ���ַ����������Ƿ����ָ���ַ�����lenΪ���鳤�ȣ�pos[]���鱣���ַ������ֵ�λ��
//����ֵ�������ڷ��أ�1�������򷵻ظ��ַ������ִ���
int isContain(string str,string contain[], int len, int pos[]);

//ָ���ַ����������Ƿ����ָ���ַ���, �����ִ�Сд��lenΪ���鳤�ȣ������򷵻�true�������ڷ���false
bool isIn(string str,string contain[], int len);

//���ܣ��õ�һ���ַ������ļ����ֵĴ���
//����ֵ������
int getCount(string test);

//���ܣ�����ַ����Ƿ���#define����
//����ֵ���Ƿ���true
bool checkDef(string test);

//���ܣ��������Ƚϼ������Ȱ�one����one��ͬ��two����
//�������������鳤����ͬ��Ϊlen
void sortTwo(int one[], int two[], int len);


//���ܣ�����ַ����Ƿ�������
//����ֵ���ǵĻ�����true,���ǵĻ�����false
bool onlyNum(string test);

#endif