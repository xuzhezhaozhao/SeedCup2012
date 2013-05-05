// һЩ��������

#include"SeedCup.h"

//��ָ����string���������򣬳���Ϊlen, ����Ҫ��ĸ�ʽ��ӡ������
void sort_string_incr(string str[], int len)
{
	int i, j;
	string temp;
	for(i=0; i<len-1; i++)
	{
		for(j=i+1; j<len; j++)
		{
			if(str[i] > str[j])
			{
				temp = str[i];
				str[i] = str[j];
				str[j] = temp;
			}
		}
	}
	for(i=0; i<len-1; i++)
	{
		cout << str[i] << ",";
	}
	cout << str[i] << endl;
}

//��ָ����string���齵���򣬳���Ϊlen, ����Ҫ��ĸ�ʽ��ӡ������
void sort_string_desc(string str[], int len)
{
	int i, j;
	string temp;
	for(i=0; i<len-1; i++)
	{
		for(j=i+1; j<len; j++)
		{
			if(str[i] < str[j])
			{
				temp = str[i];
				str[i] = str[j];
				str[j] = temp;
			}
		}
	}
	for(i=0; i<len-1; i++)
	{
		cout << str[i] << ",";
	}
	cout << str[i] << endl;
}

//����ָ�����λ�ã�����һ�� list<table>::iterator��������ʱ�޷�����
list<table>::iterator find_table(string & table_name)
{
	int i;
	list<table>::iterator iter = (*iter_current_db).db_c.begin();

	for(i=0; i<(*iter_current_db).db_c.size(); i++)
	{
		if(0 == _stricmp( table_name.c_str(), (*iter).table_name.c_str() ) )
		{
			return iter;
		}
		iter++;
	}
}

//����ָ���е��������� 0: NONE 1:int 2:float 3:string
int get_col_type(string & table_name, string & col_name)
{
	int col_num;
	list<table>::iterator iter;
	iter = find_table(table_name);
	col_num = get_col_num(iter, col_name)-1;
	return (*iter).col_type[col_num];
}

// �õ�ָ����ָ�����Ϊnum(1��ʼ)��ָ����¼��ֵ����ת���ַ�����NONE����Ϊ"#"��int, floatû�в���������õ�"#"
string get_record(list<table>::iterator iter, list<record>::iterator iter_record, int num1)
{
	int num = num1-1;
	int i, j;
	int count = 0;
	string get_str;
	char buf[50];

	int int_count = 0;
	int float_count = 0;
	int str_count = 0;
	
	for(i=0; i<50; i++)
	{
		if( (*iter).properity[i] != "")
		{
			count++;
		}
		else
			break;
	}

	switch( (*iter).col_type[num])
	{
	case 0:
		get_str = "#";
		break;

	case 1:  //int ��
		for(j=0; j<num; j++)
		{
			if(1 == (*iter).col_type[j] )
			{
				int_count++;
			}
		}

		if(-65535 == (*iter_record).int_x[int_count] )
		{
			get_str = "#";
		}
		else
		{
			sprintf(buf, "%d", (*iter_record).int_x[int_count] );
			get_str = buf;
		}
		break;

	case 2:
		for(j=0; j<num; j++)
		{
			if(2 == (*iter).col_type[j] )
			{
				float_count++;
			}
		}
		if(-65535 == (*iter_record).float_x[float_count] )
		{
			get_str = "#";
		}
		else
		{
			sprintf(buf, "%.2f", (*iter_record).float_x[float_count] );	
			get_str = buf;		
		}
		break;

	case 3:
		for(j=0; j<num; j++)
		{
			if(3 == (*iter).col_type[j] )
			{
				str_count++;
			}
		}
		if("" == (*iter_record).string_x[str_count] || "-65535" == (*iter_record).string_x[str_count])
		{
			get_str = "#";
		}
		else
		{
			get_str = (*iter_record).string_x[str_count];
		}
		break;
	
	default:
		break;
	}

	return get_str;
}

// �õ�����ţ�1��ʼ�����أ�1��ʾ�Ҳ���
int get_col_num(list<table>::iterator iter, string & col_name)
{
	int count;
	int i;
	int num1 = -1;
	count = column_count(iter);

	//�������col_name�洢������
	for(i=0; i<count; i++)
	{
		if( 0 == _stricmp(col_name.c_str(), (*iter).properity[i].c_str())) // �ҵ�ָ����
		{
			num1 = i+1;
			break;
		}
	}
	return num1;
}

//�ڵ�num+1��֮ǰ�ж�����int������
int get_int_count(list<table>::iterator iter, int num)
{
	int i;
	int int_count = 0;

	for(i=0; i<num; i++)
	{
		if(1 == (*iter).col_type[i])
		{
			int_count++;
		}
	}

	return int_count;
}

//�ڵ�num+1��֮ǰ�ж�����float������
int get_float_count(list<table>::iterator iter, int num)
{
	int i;
	int float_count = 0;

	for(i=0; i<num; i++)
	{
		if(2 == (*iter).col_type[i])
		{
			float_count++;
		}
	}

	return float_count;
}

//�ڵ�num+1��֮ǰ�ж�����str������
int get_str_count(list<table>::iterator iter, int num)
{
	int i;
	int str_count = 0;
	
	for(i=0; i<num; i++)
	{
		if(3 == (*iter).col_type[i])
		{
			str_count++;
		}
	}

	return str_count;
}

//����ָ����¼ָ����ֵ, ����-1ʱ��ʾ��NONE���͸�ֵ
int set_col_num(list<table>::iterator iter, list<record>::iterator iter_record, 
	string & col_name, string & value)
{
	int num;
	int num1=0;
	int count;

	int col_int;
	float col_float;
	string col_str;

	int int_count;
	int float_count;
	int str_count;

	num1 = get_col_num(iter, col_name);
	num = num1-1;
	count = column_count(iter);
	
	switch( (*iter).col_type[num] )
	{
	case 0:
		return -1;
		break;
	case 1:
		col_int = atoi(value.c_str());
		int_count = get_int_count(iter, num);
		(*iter_record).int_x[int_count] = col_int;
		break;
	case 2:
		col_float = atof(value.c_str());
		float_count = get_float_count(iter, num);
		(*iter_record).float_x[float_count] = col_float;
		break;
	case 3:
		col_str = value;
		str_count = get_str_count(iter, num);
		(*iter_record).string_x[str_count] = col_str;
		break;
	default:
		break;
	}

}

//ͷβ�����ţ���������������ո��������Ű���������������ַ���
string add_quote(string str)
{
	int i = 0;
	const char *temp = str.c_str();

	while('\0' != temp[i])
	{
		if(' ' == temp[i])
		{
			str = "\"" + str + "\"";
			return str;
		}
		i++;
	}

	return str;
}

//����Ҫ��ӡ���е��������, 1��ʼ��col_name�����б����ڴ�ӡ������
int generate_select( string & table_name, string col_name[], int *select)
{
	if(isExit_table(table_name))
	{
		int i = 0;
		int col_num;
		list<table>::iterator iter;
		iter = find_table(table_name);

		if(isExit_column2(table_name, col_name))
		{
			while("" != col_name[i])
			{
				col_num = get_col_num(iter, col_name[i]);
				select[i] = col_num;
				i++;
			}
			select[i] = -1;
		}
		else
		{
			cout << "error" << endl;
			return -1;
		}
	}
	else
	{
		cout << "error" << endl;
		return -1;
	}
	return 0;
}

// ���ؼ�¼��ʽ������ַ���, ����ӡ����
string display_select_record( string & table_name, string col_name[], list<record>::iterator iter_record)
{
	int  select[20];
	int i, k, m;
	int count = 0; // ��¼�������Եĸ���
	int null_flag = -1;
	string get_str[50];
	string get_slect_record = "";
	list<table>::iterator iter = (*iter_current_db).db_c.begin(); // ָ����ָʾ��

	generate_select(table_name, col_name, select); // ����select����
	iter = find_table(table_name);

	k=0;
	while(-1 != select[k])
	{
		get_str[k] =  get_record(iter, iter_record, select[k]);
		get_str[k] = add_quote(get_str[k]);
		k++;
	}

	for(i=0; i<k; i++)
	{
		if("" != get_str[i])
		{
			null_flag = 1;
			break;
		}
	}

	if(-1 == null_flag)
	{
		get_slect_record = "$";
		cout << "$" << endl;
	}
	else
	{
		for(m=0; m<k-1; m++)
		{
			get_slect_record += get_str[m] + ",";
		}
		get_slect_record += get_str[m]; // ���һ��������Ҫ����
		cout << get_slect_record << endl;
	}		
	return get_slect_record;
}

// ͳ��ָ�������ж�����, ��������
int column_count(list<table>::iterator iter)
{
	int j;
	int count = 0;
	for(j=0; j<50; j++)
	{
		if( (*iter).properity[j] != "")
		{
			count++;
		}
		else
			break;
	}

	return count;
}

//����������¼��λ��
void swap_record(list<record>::iterator iter_record1, list<record>::iterator iter_record2)
{
	struct record temp_record;
	int k;
	for(k=0; k<20; k++)
	{
		temp_record.float_x[k] = (*iter_record1).float_x[k];
		temp_record.int_x[k] = (*iter_record1).int_x[k];
		temp_record.string_x[k] = (*iter_record1).string_x[k];

		(*iter_record1).float_x[k] = (*iter_record2).float_x[k];
		(*iter_record1).int_x[k] = (*iter_record2).int_x[k];
		(*iter_record1).string_x[k] = (*iter_record2).string_x[k];

		(*iter_record2).float_x[k] = temp_record.float_x[k];
		(*iter_record2).int_x[k] = temp_record.int_x[k];
		(*iter_record2).string_x[k] = temp_record.string_x[k];
	}
}

// �����е����ݰ�ָ������������, �ձ���0
int sort_table_incr(string & table_name, string by_col_name)
{
	if(isempty_table(table_name))
	{
		return 0;
	}

	else
	{

	list<table>::iterator iter;
	list<record>::iterator iter_record1;
	list<record>::iterator iter_record2;
	list<record>::iterator iter_temp;

	struct record temp_record;

	int col_num;
	iter = find_table(table_name);
	iter_record1 = (*iter).table_c.begin(); // ָ����ĵ�һ����¼
	iter_record2 = ++iter_record1;
	--iter_record1;  // ����ʹ��iter_record2 = iter_record1+1 ʱ�ᱨ��

	int int_count;
	int float_count;
	int str_count;

	col_num = get_col_num(iter, by_col_name)-1;
	
	switch((*iter).col_type[col_num])
	{
	case 0:
		break;
	case 1:
		int_count = get_int_count(iter, col_num);
		while(iter_record1 != --(*iter).table_c.end())
		{
			iter_temp = iter_record1;
			for( iter_record2=++iter_temp; iter_record2 != (*iter).table_c.end(); iter_record2++)
			{
				if( (*iter_record1).int_x[int_count] > (*iter_record2).int_x[int_count] )  // ����ʱ�޸�
				{
					swap_record(iter_record1, iter_record2);
				}
			}
			++iter_record1;
		}
		break;

	case 2:
		float_count = get_float_count(iter, col_num);
		while(iter_record1 != --(*iter).table_c.end())
		{
			iter_temp = iter_record1;
			for( iter_record2=++iter_temp; iter_record2 != (*iter).table_c.end(); iter_record2++)
			{
				if( (*iter_record1).float_x[float_count] > (*iter_record2).float_x[float_count] )  // ����ʱ�޸�
				{
					swap_record(iter_record1, iter_record2);				
				}
			}
			++iter_record1;
		}

		break;

	case 3:
		str_count = get_str_count(iter, col_num);
		while(iter_record1 != --(*iter).table_c.end())
		{
			iter_temp = iter_record1;
			for( iter_record2=++iter_temp; iter_record2 != (*iter).table_c.end(); iter_record2++)
			{
				if( (*iter_record1).string_x[str_count] > (*iter_record2).string_x[str_count] )  // ����ʱ�޸�
				{
					swap_record(iter_record1, iter_record2);
				}
			}
			++iter_record1;
		}
		break;

	default:
		break;
	}

	}
}

int sort_table_default(string & table_name, string by_col_name)
{
	if(isempty_table(table_name))
	{
		return 0;
	}

	else
	{

	list<table>::iterator iter;
	list<record>::iterator iter_record1;
	list<record>::iterator iter_record2;
	list<record>::iterator iter_temp;

	struct record temp_record;

	int col_num;
	iter = find_table(table_name);
	iter_record1 = (*iter).table_c.begin(); // ָ����ĵ�һ����¼
	iter_record2 = ++iter_record1;
	--iter_record1;  // ����ʹ��iter_record2 = iter_record1+1 ʱ�ᱨ��

	int int_count;
	int float_count;
	int str_count;

	col_num = get_col_num(iter, by_col_name)-1;
	
	switch((*iter).col_type[col_num])
	{
	case 0:
		break;
	case 1:
		int_count = get_int_count(iter, col_num);
		while(iter_record1 != --(*iter).table_c.end())
		{
			iter_temp = iter_record1;
			for( iter_record2=++iter_temp; iter_record2 != (*iter).table_c.end(); iter_record2++)
			{
				if( (*iter_record1).int_x[int_count] > (*iter_record2).int_x[int_count] )  // ����ʱ�޸�
				{
					swap_record(iter_record1, iter_record2);
				}
			}
			++iter_record1;
		}
		break;

	case 2:
		float_count = get_float_count(iter, col_num);
		while(iter_record1 != --(*iter).table_c.end())
		{
			iter_temp = iter_record1;
			for( iter_record2=++iter_temp; iter_record2 != (*iter).table_c.end(); iter_record2++)
			{
				if( (*iter_record1).float_x[float_count] > (*iter_record2).float_x[float_count] )  // ����ʱ�޸�
				{
					swap_record(iter_record1, iter_record2);				
				}
			}
			++iter_record1;
		}

		break;

	case 3:
		str_count = get_str_count(iter, col_num);
		while(iter_record1 != --(*iter).table_c.end())
		{
			iter_temp = iter_record1;
			for( iter_record2=++iter_temp; iter_record2 != (*iter).table_c.end(); iter_record2++)
			{
				if( (*iter_record1).string_x[str_count] > (*iter_record2).string_x[str_count] )  // ����ʱ�޸�
				{
					swap_record(iter_record1, iter_record2);
				}
			}
			++iter_record1;
		}
		break;

	default:
		break;

	}
	return 1;
	}
}

// �����е����ݰ�ָ���н�������
int sort_table_desc(string & table_name, string by_col_name)
{
		if(isempty_table(table_name))
	{
		return 0;
	}

	else
	{

	list<table>::iterator iter;
	list<record>::iterator iter_record1;
	list<record>::iterator iter_record2;
	list<record>::iterator iter_temp;

	struct record temp_record;

	int col_num;
	iter = find_table(table_name);
	iter_record1 = (*iter).table_c.begin(); // ָ����ĵ�һ����¼
	iter_record2 = ++iter_record1;
	--iter_record1;  // ����ʹ��iter_record2 = iter_record1+1 ʱ�ᱨ��

	int int_count;
	int float_count;
	int str_count;

	col_num = get_col_num(iter, by_col_name)-1;
	
	switch((*iter).col_type[col_num])
	{
	case 0:
		break;
	case 1:
		int_count = get_int_count(iter, col_num);
		while(iter_record1 != --(*iter).table_c.end())
		{
			iter_temp = iter_record1;
			for( iter_record2=++iter_temp; iter_record2 != (*iter).table_c.end(); iter_record2++)
			{
				if( (*iter_record1).int_x[int_count] < (*iter_record2).int_x[int_count] )  // ����ʱ�޸�
				{
					swap_record(iter_record1, iter_record2);
				}
			}
			++iter_record1;
		}
		break;

	case 2:
		float_count = get_float_count(iter, col_num);
		while(iter_record1 != --(*iter).table_c.end())
		{
			iter_temp = iter_record1;
			for( iter_record2=++iter_temp; iter_record2 != (*iter).table_c.end(); iter_record2++)
			{
				if( (*iter_record1).float_x[float_count] < (*iter_record2).float_x[float_count] )  // ����ʱ�޸�
				{
					swap_record(iter_record1, iter_record2);
				}
			}
			++iter_record1;
		}

		break;

	case 3:
		str_count = get_str_count(iter, col_num);
		while(iter_record1 != --(*iter).table_c.end())
		{
			iter_temp = iter_record1;
			for( iter_record2=++iter_temp; iter_record2 != (*iter).table_c.end(); iter_record2++)
			{
				if( (*iter_record1).string_x[str_count] < (*iter_record2).string_x[str_count] )  // ����ʱ�޸�
				{
					swap_record(iter_record1, iter_record2);
				}
			}
			++iter_record1;
		}
		break;

	default:
		break;
	}
	}
}

// ��ͨ���*�������ַ���ƥ�亯����patָ���ͨ������ַ�����ƥ���򷵻�true����ƥ�䷵��false
bool strMatch(char *pat,char *str)
{
 char *s=NULL;
 char *p=NULL;
 bool star=false;
 bool bBreak=false;
 do 
 {
    bBreak=false;
    for(s=str,p=pat;*s;++s,++p)
    {
     switch(*p)
     {
     case '?':
      break;
     case '*':
      star=true; //����*ƥ���
      str=s;
      pat=p;
      if(!*++pat)
       return true;
      bBreak=true; //�˳�ѭ��
      break;
     default:
      if(*s!=*p)
      {
       if(!star) 
        return false;
       str++;
       bBreak=true;
      }
      break;
     }
     if(bBreak) //�˳�ѭ�� ���¿�ʼѭ��
	    break;
    }
    if(bBreak==false)
    {
    if(*p=='*')
	  ++p;
    return (!*p);
    }
 } while(true);
}

// ʵ��where������ƥ��ģʽ, û�и��ӵ��߼����㣬cmp����������ǰ��ͬ
bool where_cmp(list<table>::iterator iter, list <record>::iterator iter_record,  
	string  & col_name, string value, int cmp)
{
	int col_int; 
	float col_float;
	string col_str;  // �Ƚ�ֵ

	int int_count = 0;
	int float_count = 0;
	int str_count = 0;  //ȷ�����ݴ洢λ��

	int col_num = get_col_num(iter, col_name)-1; 
	switch((*iter).col_type[col_num])
	{
	case 0:
		return false;
		break;
	case 1:
		col_int = atoi(value.c_str());
		int_count = get_int_count(iter, col_num);
		switch(cmp)
		{
		case 0:
				if((*iter_record).int_x[int_count] == col_int)
					return true;
				else
					return false;
			break;
		case 1:
				if((*iter_record).int_x[int_count] > col_int)
					return true;
				else
					return false;
			break;
		case -1:
				if((*iter_record).int_x[int_count] < col_int)
					return true;
				else
					return false;
			break;

		case 2:
				if((*iter_record).int_x[int_count] >= col_int)
					return true;
				else
					return false;
			break;
		case -2:
				if((*iter_record).int_x[int_count] <= col_int)
					return true;
				else
					return false;
			break;
		case 3:
				if((*iter_record).int_x[int_count] != col_int)
					return true;
				else
					return false;
			break;
		}
		break;
	case 2:
		col_float = atof(value.c_str());
		float_count = get_float_count(iter, col_num);
		switch(cmp)
		{
		case 0:
				if((*iter_record).float_x[float_count] == col_float)
					return true;
				else
					return false;
			break;
		case 1:
				if((*iter_record).float_x[float_count] > col_float)
					return true;
				else
					return false;
			break;
		case -1:
				if((*iter_record).float_x[float_count] < col_float)
					return true;
				else
					return false;
			break;

		case 2:
				if((*iter_record).float_x[float_count] >= col_float)
					return true;
				else
					return false;
			break;
		case -2:
				if((*iter_record).float_x[float_count] <= col_float)
					return true;
				else
					return false;
			break;
		case 3:
				if((*iter_record).float_x[float_count] != col_float)
					return true;
				else
					return false;
			break;
		}
		break;
	case 3:
		col_str = value;
		str_count = get_str_count(iter, col_num);
		switch(cmp)
		{
		case 0:
				if((*iter_record).string_x[str_count] == col_str)
					return true;
				else
					return false;
			break;
		case 1:
				if((*iter_record).string_x[str_count] > col_str)
					return true;
				else
					return false;
			break;
		case -1:
				if((*iter_record).string_x[str_count] < col_str)
					return true;
				else
					return false;
			break;

		case 2:
				if((*iter_record).string_x[str_count] >= col_str)
					return true;
				else
					return false;
			break;
		case -2:
				if((*iter_record).string_x[str_count] <= col_str)
					return true;
				else
					return false;
			break;
		case 3:
				if((*iter_record).string_x[str_count] != col_str)
					return true;
				else
					return false;
			break;
		}
		break;
	}
	return false;
}
bool where_between(list<table>::iterator iter, list <record>::iterator iter_record, 
	string & col_name, string value1, string value2)
{
	int int_temp;
	float float_temp;

	int int_value1, int_value2;
	float float_value1, float_value2;

	int int_count;
	int float_count;

	int col_num = get_col_num(iter, col_name)-1;  // �õ��кţ�0��ʼ

	switch((*iter).col_type[col_num])
	{
	case 0:
		return false;
		break;
	case 1:
		int_count = get_int_count(iter, col_num); 
		int_value1 = atoi(value1.c_str());
		int_value2 = atoi(value2.c_str());
		if(int_value1 > int_value2)
		{
			int_temp = int_value1;
			int_value1 = int_value2;
			int_value2 = int_temp;
		}
		
		if( (*iter_record).int_x[int_count] > int_value1 && (*iter_record).int_x[int_count] < int_value2 )  //*****
			return true;
		else
			return false;
		break;

	case 2:
		float_count = get_float_count(iter, col_num); 
		float_value1 = atof(value1.c_str());
		float_value2 = atof(value2.c_str());
		if(float_value1 > float_value2)
		{
			float_temp = float_value1;
			float_value1 = float_value2;
			float_value2 = float_temp;
		}
		if( (*iter_record).float_x[float_count] > float_value1 && (*iter_record).float_x[float_count] < float_value2 )  //*****
			return true;
		else
			return false;
		break;

	case 3:
		return false;
		break;

	default:
		return false;
		break;
	}
}
bool where_like(list<table>::iterator iter, list <record>::iterator iter_record, 
	string & like_col_name, string & like_value)
	
{
	char pat_str[100];
	char str[100];
	string like_value_str;

	int str_count;
	int col_num = get_col_num(iter, like_col_name)-1;  // �õ��кţ�0��ʼ

	switch((*iter).col_type[col_num])
	{
	case 0:
		return false;
		break;
	case 1:
		return false;
		break;

	case 2:
		return false;
		break;

	case 3:
		like_value_str = like_value;
		str_count = get_str_count(iter, col_num);
		
		strcpy(str, (*iter_record).string_x[str_count].c_str());
		strcpy(pat_str, like_value_str.c_str());

		if( strMatch(pat_str, str) )  //*****
			return true;
		else
			return false;
	}
}

//�ж��Ƿ�Ϊ�ձ��Ƿ���true
bool isempty_table(string table_name)
{
	list<table>::iterator iter;
	iter = find_table(table_name);
	if(0 == (*iter).table_c.size())
	{
		return true;
	}
	else
	{
		return false;
	}
}