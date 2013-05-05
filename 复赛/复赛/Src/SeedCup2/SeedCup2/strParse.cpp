// �Զ����һ���ַ������д����Է������Ľ���

#include"SeedCup2.h"

//���ܣ����ַ�����ɢ���ֱ�˳��ֱ������single������,���ش�ɢ���ַ����ĸ���
int covertCmd(string & str, string single[])
{

	str = str + " "; // �Ӹ��ո��������һ���ַ�Ϊ�������ַ���bug
	formatCmd(str);

	int len = getSingle(str, single);
	for(int i=0; i<len; i++)
	{
		encodeStr(single[i]);
	}
	return len;
} 

//���ܣ����ַ����еķ��ţ���>,<,�ֺ�,����,����֮�ࣩǰ��ӿո�$����ո񣬼����ߵ��ַ�����һ���ַ���
void formatCmd(string & sentence)
{
	saveBlank(sentence);
	addBlank(sentence);
	addBlank2(sentence);
}

//���ܣ���( ) [ ]  { } , ; ' " : ?�ַ�ǰ��ӿո�
void addBlank(string & sentence)
{
	int i, j;
	int len = sentence.size();
	char formatStr[1000];
	j = 0;
	for(i=0; i<len; i++)
	{
		if( ('(' == sentence[i] || ')' == sentence[i]) 
			|| (']' == sentence[i] || '[' == sentence[i]) 
			|| ('}' == sentence[i] || '{' == sentence[i]) 
			|| (',' == sentence[i] || ';' == sentence[i])
			|| ('\'' == sentence[i] || '\"' == sentence[i])
			|| (':' == sentence[i] || '?' == sentence[i]) )
		{
			formatStr[j] = ' ';
			formatStr[j+1] = sentence[i];
			formatStr[j+2] = ' ';
			j = j+3;
		}
		else
		{
			formatStr[j] = sentence[i];
			j++;
		}
	}
	formatStr[j] = '\0';

	sentence = formatStr;
}

//���ܣ���'+','-','/','>','<','=','>=','<=', '!=', '==', '++', '--','+=', '-=', '*=',
// '/=', '|', '&', '||', '&&', '*', '**', '/*', '*/'ǰ��ӿո�
void addBlank2(string & sentence)
{
	int i, j;
	int len = sentence.size();
	char formatStr[1000];
	j = 0;
	for(i=0; i<len; i++)
	{
		if( ('>' == sentence[i] && '=' != sentence[i+1]) || 
			('<' == sentence[i] && '=' != sentence[i+1]) ||
			('=' == sentence[i] && '=' != sentence[i+1]) ||
			('&' == sentence[i] && '&' != sentence[i+1]) || 
			('|' == sentence[i] && '|' != sentence[i+1]) ||
			('*' == sentence[i] && '*' != sentence[i+1]) && ('/' != sentence[i+1]) ||
			('+' == sentence[i] && '=' != sentence[i+1]) && ('+' != sentence[i+1]) ||
			('-' == sentence[i] && '=' != sentence[i+1]) && ('-' != sentence[i+1]) ||
			('/' == sentence[i] && '=' != sentence[i+1]) && ('*' != sentence[i+1]) )
		{
			formatStr[j] = ' ';
			formatStr[j+1] = sentence[i];
			formatStr[j+2] = ' ';
			j = j+3;
		}
		else if ( ('>' == sentence[i] && '=' == sentence[i+1]) || 
				  ('<' == sentence[i] && '=' == sentence[i+1]) || 
				  ('!' == sentence[i] && '=' == sentence[i+1]) ||
				  ('=' == sentence[i] && '=' == sentence[i+1]) ||
				  ('+' == sentence[i] && '+' == sentence[i+1]) || 
				  ('-' == sentence[i] && '-' == sentence[i+1]) ||
				  ('+' == sentence[i] && '=' == sentence[i+1]) ||
				  ('-' == sentence[i] && '=' == sentence[i+1]) ||
				  ('*' == sentence[i] && '=' == sentence[i+1]) ||
				  ('/' == sentence[i] && '=' == sentence[i+1]) ||
				  ('|' == sentence[i] && '|' == sentence[i+1]) || 
				  ('&' == sentence[i] && '&' == sentence[i+1]) ||
				  ('*' == sentence[i] && '*' == sentence[i+1]) ||
				  ('/' == sentence[i] && '*' == sentence[i+1]) ||
				  ('*' == sentence[i] && '/' == sentence[i+1]) )
		{
			formatStr[j] = ' ';
			formatStr[j+1] = sentence[i];
			formatStr[j+2] = sentence[i+1];
			formatStr[j+3] = ' ';
			j = j+4;
			i = i+1;
		}
		else
		{
			formatStr[j] = sentence[i];
			j++;
		}
	}
	formatStr[j] = '\0';

	sentence = formatStr;
}

//���ܣ���"Who I am" ת�� "who$I$am"
void saveBlank(string & sentence)
{
	int i, j;
	int len = sentence.size();
	char formatStr[1000];
	j = 0;
	for(i=0; i<len; i++)
	{
		if('\"' == sentence[i])
		{
			formatStr[i] = sentence[i];
			j=i+1;
			while('\"' != sentence[j])
			{
				if(' ' == sentence[j])
				{
					formatStr[j] = '$';
					j++;
				}
				else
				{
					formatStr[j] = sentence[j];
					j++;
				}
			}
			formatStr[j] = '\"';
			i=j;
		}
		else
		{
			formatStr[i] = sentence[i];
		}

	}
	formatStr[len] = '\0';
	sentence = formatStr;
}

//���ܣ����ַ����е�'$'��Ϊ' '�ո�
void encodeStr(string & cut)
{
	string temp;
	int i = 0;
	int len = cut.size();
	for(i=0; i<len; i++)
	{
		if('$' == cut[i])
		{
			cut[i] = ' ';
		}
	}
}

//���ܣ����Կո��Ʊ���ָ����ַ������η���single�����У����س���
int getSingle(string & str, string single[])
{
	int i, j, k;
	int len = 0;
	str = " " + str + " ";
	char temp[500];
	strcpy(temp, str.c_str());
	char temp2[1000][20];

	for(i=0; i<str.size(); i++)
	{
		if(' ' == temp[i] || '\t' == temp[i])
		{
			continue;
		}
		else if((' ' != temp[i] && '\t' != temp[i]) && 
			(' ' == temp[i-1] || '\t' == temp[i-1]))
		{
			j = i;
			k = 0;
			while(' ' != temp[j] && '\t' != temp[j])
			{
				temp2[len][k] = temp[j];
				j++;
				k++;
			}
			temp2[len][k] = '\0';
			len++;
		}
	}
	for(i=0; i<len; i++)
	{
		single[i] = temp2[i];
	}

	return len;
}