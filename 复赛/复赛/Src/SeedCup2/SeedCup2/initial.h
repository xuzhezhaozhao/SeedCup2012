#ifndef _INITIAL_H_
#define _INITIAL_H_

using namespace std;

//���ܣ���ȡ���ȫ�ֱ���������ע����Ϊ��
void initial(string inputFile);

//���ܣ����ܣ���ȡָ���ļ���ÿ�е�ȫ�ֱ���command[]�б��棬����Ҳ�㣬cmdCount�б���������������
void readFile(string inputFile);

//���ܣ�������ע����Ϊ��
void delRowsAnnotation();

//���ܣ�ɾ��ע��, ����ɾ���м�ע��
void delAnnotation();

//���ܣ����滻, �����������Ͳ������������
void macroReplace();

//���ܣ����������ĺ��滻��#define MAX (100*100)
void macroSimpleReplace();

//���ܣ��������ĺ��滻
void macroComplexReplace();

//���ܣ��õ��������ĺ�Ĳ����������䱣����macroVarName������
//������macro �궨�����
//����ֵ����������
int getMacroVarName(string macro, string macroVarName[]);

//���ܣ��ж�һ������Ƿ��Ǵ������ĺ궨�����
//����ֵ���Ƿ���true
bool isComplexMacroDef(string test);

//���ܣ���#define MAX(a, b) ((a)*(b))  �õ�((a)*(b)) ��ɢ����ַ�������
//������macro �궨�����
//����ֵ�����鳤��
int getComplexMacroValue(string macro, string complexMacroValue[]);

//���ܣ��õ�ʹ�ô��εĺ��еĴ��ݵ�ֵ����MAX(2, (3)) �е�2��(3)
//������macroName ������ useMacro ���øú����䣬macroVarLen ��θ���
//����ֵ�����ؽ����õĺ��ɢ����ַ�������ĳ���
int getComplexMacroRealValue(string macroName, string useMacro, int macroVarLen, string macroRealValue[]);

//���ܣ�չ�����������˴������ĺ�����
//������macroDef �궨����䣬 useMacro ������䣬
//����ֵ������չ��������
string singleComplexMacroReplace(string macroDef, string useMacro);

//���ܣ�ɾ���ַ�����˫����֮������, ����˫����
void delString(string & str);

//���ܣ�ɾ����ȡ���Ĵ����е�˫����֮�������
void delCmdString();

#endif