#include"SeedCup.h"

// �ַ�������


//���������ַ��������ؼ��ֺͲ���������ȡ��������single�������棬�����ַ�������
//ȥ������ķ��ţ����ţ����ţ��������š�������
int covert_sentence(string & str, string single[])
{

	format_sentence(str);

	int len = get_single(str, single);
	for(int i=0; i<len; i++)
	{
		encode_str(single[i]);
	}
	return len;
} 

// ��ʽ���ַ�������ʽ��ʽ�������漸����������ʽ�����ظ�ʽ������ַ���
// #������ַ���Ϊ�գ�$����ո񣬼����ߵ��ַ�����һ���ַ���
void format_sentence(string & sentence)
{
	save_blank(sentence);
	add_blank3(sentence);
	null_to(sentence);
	add_blank(sentence);
	add_blank2(sentence);
	to_blank(sentence);
}

void null_to(string & sentence)
{
	int i, j;
	int len = sentence.size();
	char format_str[1000];
	j = 0;
	for(i=0; i<len; i++)
	{
		if( ('(' == sentence[i] && ',' == sentence[i+1]) || 
			(',' == sentence[i] && ',' == sentence[i+1]) ||
			(',' == sentence[i] && ')' == sentence[i+1]) )
		{
			format_str[j] = sentence[i];
			format_str[j+1] = '#';
			format_str[j+2] = sentence[i+1];
			i++;
			j = j+3;
		}
		else
		{
			format_str[j] = sentence[i];
			j++;
		}
	}
	format_str[j] = '\0';
	sentence = format_str;

}

// ��'(',')',',','[',']'�ַ�ǰ��ӿո�
void add_blank(string & sentence)
{
	int i, j;
	int len = sentence.size();
	char format_str[1000];
	j = 0;
	for(i=0; i<len; i++)
	{
		if( ('(' == sentence[i] || ')' == sentence[i]) 
			|| (']'  == sentence[i] || '['  == sentence[i]) )
		{
			format_str[j] = ' ';
			format_str[j+1] = sentence[i];
			format_str[j+2] = ' ';
			j = j+3;
		}
		else
		{
			format_str[j] = sentence[i];
			j++;
		}
	}
	format_str[j] = '\0';

	sentence = format_str;
}

// ��'>','<','==','>=', '<=', '~='ǰ��ӿո�
void add_blank2(string & sentence)
{
	int i, j;
	int len = sentence.size();
	char format_str[1000];
	j = 0;
	for(i=0; i<len; i++)
	{
		if( ('>' == sentence[i] && '=' != sentence[i+1]) || 
			('<' == sentence[i] && '=' != sentence[i+1])  )  // ����'>', '<'
		{
			format_str[j] = ' ';
			format_str[j+1] = sentence[i];
			format_str[j+2] = ' ';
			j = j+3;
		}
		else if ( ('>' == sentence[i] && '=' == sentence[i+1]) || 
				  ('<' == sentence[i] && '=' == sentence[i+1]) || 
				  ('~' == sentence[i] && '=' == sentence[i+1]) ||
				   ('=' == sentence[i] && '=' == sentence[i+1]) ) // ����'>=','<=', '~=', '=='
		{
			format_str[j] = ' ';
			format_str[j+1] = sentence[i];
			format_str[j+2] = sentence[i+1];
			format_str[j+3] = ' ';
			j = j+4;
			i = i+1;
		}
		else
		{
			format_str[j] = sentence[i];
			j++;
		}
	}
	format_str[j] = '\0';

	sentence = format_str;
}

// ����select *name�������like[f*]����
void add_blank3(string & sentence)
{
	int i, j;
	int len = sentence.size();
	char format_str[1000];
	j = 0;
	for(i=0; i<len; i++)
	{
		if(i<20 && ('*' == sentence[i]))
		{
			format_str[j] = ' ';
			format_str[j+1] = sentence[i];
			format_str[j+2] = ' ';
			j = j+3;
		}
		else
		{
			format_str[j] = sentence[i];
			j++;
		}
	}

	format_str[j] = '\0';
	sentence = format_str;
}

//��',', '\'', '\"', ';' ת�ɿո�
void to_blank(string & sentence)
{
	int i, j;
	int len = sentence.size();
	char format_str[1000];
	j = 0;
	for(i=0; i<len; i++)
	{
		if('\'' == sentence[i] || '\"' == sentence[i] || ',' == sentence[i] || ';' == sentence[i])
		{
			format_str[j] = ' ';
			j++;
		}
		else
		{
			format_str[j] = sentence[i];
			j++;
		}
	}
	format_str[j] = '\0';

	sentence = format_str;
}

//aa'Who I am' ת�� 'who$I$am'
void save_blank(string & sentence)
{
	int i, j;
	int len = sentence.size();
	char format_str[1000];
	j = 0;
	for(i=0; i<len; i++)
	{
		if('\'' == sentence[i])
		{
			format_str[i] = sentence[i];
			j=i+1;
			while('\'' != sentence[j])
			{
				if(' ' == sentence[j])
				{
					format_str[j] = '$';
					j++;
				}
				else
				{
					format_str[j] = sentence[j];
					j++;
				}
			}
			format_str[j] = '\'';
			i=j;
		}
		else
		{
			format_str[i] = sentence[i];
		}

	}
	format_str[len] = '\0';
	sentence = format_str;
}

// ����Ƿ�Ϊ�ؼ��֣������ִ�Сд���Ƿ���true�����Ƿ���false
bool iskeyword(string test_word)
{
	string keyword[32]={"int", "float", "text", "create","use","table","database", "databases", "alter","truncate",\
		"add","column","drop","rename","select","update","delete","insert","into","set","values","show",\
		"where","order","from","and","or","desc","incr","by","like","between"};
	int i;

	for(i=0; i<32; i++)
	{
		if(0 == _stricmp(test_word.c_str(), keyword[i].c_str()))
			return true;
	}

	return false;
}

//�ַ���Ϊ "#", ��Ϊ�գ������ַ����е�'$'��Ϊ' '�ո�
void encode_str(string & cut)
{
	string temp;
	int i = 0;
	int len = cut.size();
	if(1 == len && '#' == cut[0])
	{
		cut = "";
	}
	else
	{
		for(i=0; i<len; i++)
		{
			if('$' == cut[i])
			{
				cut[i] = ' ';
			}
		}
	}
}

//����Ƿ���ڸ����Ƶ����ݿ⣬�����򷵻�1�������ڷ���0
int is_exit_db(string & database_name)
{
	int i;
	int flag = 0;
	list<db>::iterator iter = all_db.begin();

	for(i=0; i<all_db.size(); i++)
	{
		if(0 == _stricmp( database_name.c_str(), (*iter++).db_name.c_str() ) )
		{
			flag = 1;
			return flag;
		}
	}

	return flag;
}

float calc(float a, char opr, float b)
{
	 switch(opr)
	 {
	 case  '+':
	  return a+b;

	 case '-':
	  return a-b;

	 case '*':
	  return a*b;
	
	 case '/':
		 if(0 == b)
		 {
			 divider = true;
			 return 1;
		 }
		 else
			return a/b;
		 break;
 }
 return 0;
}

//�ж����ȼ���
//С�� ���� false
//���� ���� true
int GetLevel(char opr)
{
 switch(opr)
 {
 case '+':
 case '-':
  return 1;
 case '*':
 case '/':
  return 2;
 case '(':
 case ')':
  return 0;
 }
 return 0;
}


//����ջ 
float yunsuan(string &str_in)
{
 stack<float> data;
 stack<char> opr;
string calcStr = str_in;
	int ab;
	const char* s="";
	float stra;
	string str;
 for (int i = 0; i < (int)calcStr.length(); i++)
 {
  //����
	 if (isdigit(calcStr[i]))
	 {
		 ab =calcStr.find_first_of("+-*/()",i);
		
		 str=calcStr.substr(i,ab-i);
		 i=ab-1;
		 s=str.c_str();
		 stra=(float)atof(s);
//		 calcStr[i]=aaa;
		 data.push(stra);
	 }
  //����
  else
  {
   //3������ѷ�����ջ
   if (opr.empty() || (calcStr[i] == '(') || (GetLevel(calcStr[i]) > GetLevel(opr.top()) )) 
   {
    opr.push(calcStr[i]);
   }
   //����ջ�����
   else
   {
    //���� )
    if ( calcStr[i] == ')')
    {
     while(opr.top() != '(')
     {
      float b = data.top();
      data.pop();

      float a = data.top();
      data.pop();

      float result = calc(a, opr.top(), b);
      opr.pop();

      data.push(result);
     }
     //pop '('
     opr.pop();

    }
    // + - * /
    else
    {
      float b = data.top();
      data.pop();

      float a = data.top();
      data.pop();

      float result = calc(a, opr.top(), b);
      opr.pop();

      data.push(result);
      opr.push(calcStr[i]);
    }
   }
  }
 }


 while(!opr.empty())
 {
  float b = data.top();
  data.pop();

  float a = data.top();
  data.pop();

  float result = calc(a, opr.top(), b);
  opr.pop();

  data.push(result);
 }
// printf("%s\n",calcStr.c_str());
 //printf("%.2f", data.top());
 return data.top();
}


int math_to(string &str)
{
	int pose,pose1,pose2;
	unsigned int i;
	string str_temp;
	string str1=str;
	
	for(i=0;i<str.size();i++)
	{
		if((str[i]>='A')&&(str[i]<='Z'))
			str[i]=str[i]-'A'+'a';
	}
	pose=str.find(" where ");
	if(pose!=-1)
	{
		pose1=str.find("(",pose);
		pose2=str.rfind(")");
		if((pose1!=-1)&&(pose2!=-1))
		{
			str_temp=str.substr(pose1,pose2-pose1+1);
			delete_blank(str_temp);
			float ans=yunsuan(str_temp);
			char temp[100]="";
			char* str_=temp;
			sprintf(str_,"%.2f",ans);
			string str_s=str_;
			str1.replace(pose1,pose2-pose1+1,str_s+" ");
		}
	}
	str=str1;
	return 0;
}

//���Կո񣬻��У��Ʊ���ָ����ַ������η���single�����У����س���
int get_single(string & str, string single[])
{
	int i, j, k;
	int len = 0;
	str = ' ' + str;
	char temp[500];
	strcpy(temp, str.c_str());
	char temp2[1000][20];

	for(i=0; i<str.size(); i++)
	{
		if(' ' == temp[i] || '\n' == temp[i] || '\t' == temp[i])
		{
			continue;
		}
		else if((' ' != temp[i] && '\n' != temp[i] && '\t' != temp[i]) && 
			(' ' == temp[i-1] || '\n' == temp[i-1] || '\t' == temp[i-1]))
		{
			j = i;
			k = 0;
			while(' ' != temp[j] && '\n' != temp[j] && '\t' != temp[j])
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

int delete_blank(string &str)
{
    string::iterator   it;
    for (it =str.begin(); it != str.end(); ++it)
    {
        if ( *it == ' ')
        {
            str.erase(it);
        }
    }
	return 0;
}