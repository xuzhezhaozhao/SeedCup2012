// 对读入的一行字符串进行处理，以方便后面的解析

#include"SeedCup2.h"

//功能：将字符串打散，分别按顺序分别存入在single数组中,返回打散的字符串的个数
int covertCmd(string & str, string single[])
{

	str = str + " "; // 加个空格消除最后一个字符为待处理字符的bug
	formatCmd(str);

	int len = getSingle(str, single);
	for(int i=0; i<len; i++)
	{
		encodeStr(single[i]);
	}
	return len;
} 

//功能：在字符串中的符号（如>,<,分号,逗号,括号之类）前后加空格，$代表空格，即两边的字符串是一个字符串
void formatCmd(string & sentence)
{
	saveBlank(sentence);
	addBlank(sentence);
	addBlank2(sentence);
}

//功能：在( ) [ ]  { } , ; ' " : ?字符前后加空格
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

//功能：在'+','-','/','>','<','=','>=','<=', '!=', '==', '++', '--','+=', '-=', '*=',
// '/=', '|', '&', '||', '&&', '*', '**', '/*', '*/'前后加空格
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

//功能：将"Who I am" 转成 "who$I$am"
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

//功能：将字符串中的'$'置为' '空格
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

//功能：将以空格，制表符分隔的字符串依次放入single数组中，返回长度
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