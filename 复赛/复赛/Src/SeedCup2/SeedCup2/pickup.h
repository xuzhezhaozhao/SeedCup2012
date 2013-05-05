#ifndef _PICK_UP_H_
#define _PICK_UP_H_

using namespace std;

// ���ܣ�����һ�����������йص������д�command[]��ȡ�������뵽func�����У�
//+ ��command[]��beginλ��(0��ʼ)��ʼ���Һ�����ֻ�����ҵ��ĵ�һ������������main����
//+ �� void func(){int i=1;
//+			int j=8;
//+		}  
//+ ���䰴�д���func[]��,�������ԭʼ���û�о�������
//����ֵ�����ض�ȡ�ĺ�����һ���кż�1��ֵ,��֮��û���ҵ������򷵻أ�1
//������begin������ʼλ�ã�func_len�Ǹú�����������
int getFunc(string func[], int begin,  int & func_len);

//���ܣ���ȡָ���������ĺ���
void getFuncFromName(string func[], int & func_len, string funcName);

// ���ܣ���#define����ĺ�������׷�ӵ�def������,��#define MAX 100, ��MAX����def
// ���أ����غ����
int getDefine(string def[]);

//���ܣ��õ������еı������������β���
//������������begin������ʼλ�ã�ֻ�����ҵ��ĵ�һ������
//����ֵ����������
int getFuncVar(string funcVar[], int begin);

//���ܣ���һ�������������(������const,sttic,signed,unsigned,extern��ͷ)�еı���������funVar[len]��len��ԭ�е����鳤�ȣ��������Ա���ԭ���ı���,
//+���ܵõ������������β����� ��int const**i, j, k, m;
void getVar1(string single[], int slen, string funcVar[], int & len);

//���ܣ�����getVar1,����������ʶ��signed �� unsigned
void getVar2(string single[], int slen, string funcVar[], int & len);

//���ܣ�����getVar2,�������������������ʶ��const��ͷ��
void getVar3(string single[], int slen, string funcVar[], int & len);

//���ܣ�����getVar3,�������������������ʶ��extern��ͷ��
void getVar4(string single[], int slen, string funcVar[], int & len);

//���ܣ���getVar2()�������ƣ��������������������ʶ�������������β�����������ֵ���Ͳ�����const,[un]singed,extern,static���� void func(signed int const* p1, float *const p2)
void getVar5(string single[], int slen, string funcVar[], int & len);

//���ܣ���getVar5()�������ƣ�������������������˷���ֵ���Ͱ���const,[un]singed,extern,static���� static void func(signed int const* p1, float *const p2)
void getVar6(string single[], int slen, string funcVar[], int & len);

//���ܣ��ۺ�getVar,������һ�������ж���Ĳ�����
void getVar(string cmd, string funcVar[], int & len);

//���ܣ��õ�ȫ�ֱ�����
//����ֵ��ȫ�ֱ������鳤��
int getGlobeVar(string globeVar[]);


//���ܣ��õ�ȫ���ĺ���������Ӧ�ķ���ֵ���ͣ�0��ʾvoid,1��ʾ����������main����
//����ֵ�����鳤��
int getFuncName(string funcName[], int returnType[]);

//���ܣ��õ�������������к�����������ֵ���ͣ�����ֵ���ͱ�����returnType�У�0��ʾvoid, 1��ʾ����
//����ֵ��������
string getFuncStaName(string single[], int slen, int & returnType);

//���ܣ��õ�ָ�����������λ��(0��ʼ)
//����ֵ��λ�ã������ڷ��أ�1
int getFuncPosFromName(string funcName);

//���ܣ��ж�cmp����û����std�е�Ԫ�أ��еĻ�׷�Ӵ���get������
//������len1 std���ȣ�len2 cmp����, len3 get����
void haveGet(string std[], int len1, string cmp[], int len2, string get[], int & len3);
#endif