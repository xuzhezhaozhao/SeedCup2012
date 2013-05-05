// str_parse2.cpp�еĺ�������
// �Զ����һ���ַ������д����Է������Ľ���

#ifndef _STR_PARSE_
#define _STR_PARSE_ 

using namespace std;

//���ַ�����ɢ���ֱ�˳��ֱ������single������
int covertCmd(string & str, string single[]);

//���ַ����еķ��ţ���>,<,�ֺ�,����,����֮�ࣩǰ��ӿո�$����ո񣬼����ߵ��ַ�����һ���ַ���
void formatCmd(string & sentence);

// ��( ) [ ] { }, ; ' " : ? �ַ�ǰ��ӿո�
void addBlank(string & sentence);

// ��'>','<','>=','<=', '!=', '==', '++', '--','+=', '-=', '*=', '/=', '||', '&&'ǰ��ӿո�
void addBlank2(string & sentence);

//��"Who I am" ת�� "who$I$am"
void saveBlank(string & sentence);

//���ַ����е�'$'��Ϊ' '�ո�
void encodeStr(string & cut);

//���Կո��Ʊ���ָ����ַ������η���single�����У����س���
int getSingle(string & str, string single[]);


#endif

