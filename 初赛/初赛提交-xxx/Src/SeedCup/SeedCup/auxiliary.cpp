// 一些辅助函数

#include"SeedCup.h"

//对指定的string数组升排序，长度为len, 并按要求的格式打印出内容
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

//对指定的string数组降排序，长度为len, 并按要求的格式打印出内容
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

//查找指定表的位置，返回一个 list<table>::iterator，表不存在时无法纠错
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

//返回指定列的数据类型 0: NONE 1:int 2:float 3:string
int get_col_type(string & table_name, string & col_name)
{
	int col_num;
	list<table>::iterator iter;
	iter = find_table(table_name);
	col_num = get_col_num(iter, col_name)-1;
	return (*iter).col_type[col_num];
}

// 得到指定表指定序号为num(1起始)列指定记录的值，并转成字符串，NONE类型为"#"，int, float没有插入数据则得到"#"
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

	case 1:  //int 型
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

// 得到列序号，1起始，返回－1表示找不到
int get_col_num(list<table>::iterator iter, string & col_name)
{
	int count;
	int i;
	int num1 = -1;
	count = column_count(iter);

	//下面查找col_name存储在哪里
	for(i=0; i<count; i++)
	{
		if( 0 == _stricmp(col_name.c_str(), (*iter).properity[i].c_str())) // 找到指定列
		{
			num1 = i+1;
			break;
		}
	}
	return num1;
}

//在第num+1列之前有多少列int型数据
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

//在第num+1列之前有多少列float型数据
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

//在第num+1列之前有多少列str型数据
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

//设置指定记录指定列值, 返回-1时表示给NONE类型赋值
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

//头尾加引号，如果字条串包含空格，则用引号包起来，返回这个字符串
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

//生成要打印的列的序号数组, 1起始，col_name数组中保存在打印的列名
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

// 返回记录格式化后的字符串, 并打印出来
string display_select_record( string & table_name, string col_name[], list<record>::iterator iter_record)
{
	int  select[20];
	int i, k, m;
	int count = 0; // 记录表中属性的个数
	int null_flag = -1;
	string get_str[50];
	string get_slect_record = "";
	list<table>::iterator iter = (*iter_current_db).db_c.begin(); // 指向表的指示器

	generate_select(table_name, col_name, select); // 生成select数组
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
		get_slect_record += get_str[m]; // 最后一个结束不要逗号
		cout << get_slect_record << endl;
	}		
	return get_slect_record;
}

// 统计指定表中有多少列, 返回列数
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

//交换两条记录的位置
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

// 将表中的数据按指定列升序排列, 空表返回0
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
	iter_record1 = (*iter).table_c.begin(); // 指定表的第一条记录
	iter_record2 = ++iter_record1;
	--iter_record1;  // 这是使用iter_record2 = iter_record1+1 时会报错

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
				if( (*iter_record1).int_x[int_count] > (*iter_record2).int_x[int_count] )  // 降序时修改
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
				if( (*iter_record1).float_x[float_count] > (*iter_record2).float_x[float_count] )  // 降序时修改
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
				if( (*iter_record1).string_x[str_count] > (*iter_record2).string_x[str_count] )  // 降序时修改
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
	iter_record1 = (*iter).table_c.begin(); // 指定表的第一条记录
	iter_record2 = ++iter_record1;
	--iter_record1;  // 这是使用iter_record2 = iter_record1+1 时会报错

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
				if( (*iter_record1).int_x[int_count] > (*iter_record2).int_x[int_count] )  // 降序时修改
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
				if( (*iter_record1).float_x[float_count] > (*iter_record2).float_x[float_count] )  // 降序时修改
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
				if( (*iter_record1).string_x[str_count] > (*iter_record2).string_x[str_count] )  // 降序时修改
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

// 将表中的数据按指定列降序排列
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
	iter_record1 = (*iter).table_c.begin(); // 指定表的第一条记录
	iter_record2 = ++iter_record1;
	--iter_record1;  // 这是使用iter_record2 = iter_record1+1 时会报错

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
				if( (*iter_record1).int_x[int_count] < (*iter_record2).int_x[int_count] )  // 降序时修改
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
				if( (*iter_record1).float_x[float_count] < (*iter_record2).float_x[float_count] )  // 降序时修改
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
				if( (*iter_record1).string_x[str_count] < (*iter_record2).string_x[str_count] )  // 降序时修改
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

// 带通配符*，？的字符串匹配函数，pat指向带通配符的字符串，匹配则返回true，不匹配返回false
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
      star=true; //出现*匹配符
      str=s;
      pat=p;
      if(!*++pat)
       return true;
      bBreak=true; //退出循环
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
     if(bBreak) //退出循环 重新开始循环
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

// 实现where的三种匹配模式, 没有复杂的逻辑运算，cmp代表意义与前相同
bool where_cmp(list<table>::iterator iter, list <record>::iterator iter_record,  
	string  & col_name, string value, int cmp)
{
	int col_int; 
	float col_float;
	string col_str;  // 比较值

	int int_count = 0;
	int float_count = 0;
	int str_count = 0;  //确定数据存储位置

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

	int col_num = get_col_num(iter, col_name)-1;  // 得到行号，0起始

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
	int col_num = get_col_num(iter, like_col_name)-1;  // 得到行号，0起始

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

//判断是否为空表，是返回true
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