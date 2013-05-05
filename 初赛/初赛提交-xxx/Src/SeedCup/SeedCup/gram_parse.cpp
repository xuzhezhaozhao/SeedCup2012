#include"SeedCup.h"

//判断命令是条命令形式，结果保存在全局变量gram中
/*
1.	Create: 
	Create Database database_name  建库   1
	Create Table (column1 INT, column2 FLOAT, column3 TEXT)  建表  2 

2.	Alter Table:
	Alter Table table_name Add column_name  INT 添加列   3
	Alter Table table_name Drop Column column_name 删除列 4
	Alter Table table_name Alter Column column_name INT  修改列数据类型 5

3.	Truncate:
	Truncate Table table_name   //保留结构   6

4.	Use:
	Use database_name //使用数据库   7

5.	Drop:
	Drop database_name  // 删除库   8
	Drop database_name table_name //删除表   9

6.	Rename:
	Rename Table old_name new_name // 重命名表  10
	Rename Database old_name new_name //重命名库  11

7.	Update:
	Update table_name Set (col1,col2,...)=(new_value1,new_value2,...) Where col_name==old_value // 修改表中数据   12 

8.	Delete:  
	Delete From table_name Where col_name == value  //删除表中部分数据   13

9.	Insert
	Insert Into table_name Values(value1, value2,...) //添加记录 14
	Insert Into talbe_name (col1, col2, ...) Values(value1, value2,...)  // value可以为空，用逗号分隔，(, 'yao',,'wuhan')  15

10.	Show
	Show DatabaseS Order By DESC\Incr  // 打印所有的库  16
	Show database_name Table Order By DESC\INCR   //打印指定库的表 17
	Show Table Order By Desc\Incr // 打印当前数据库中的表  18
	Show table_name Column Order By DESC\Incr  //打印指定表的所有列 19

11.	Select:
	Select column_name1,column_name2... From table_name Order By col_name Desc\Inrc    //order by 为可选参数，不选默认为升序 20
	Select column_name1, column_name2... From table_name Where cmp_col_name >= cmp_value Order By col_name Desc\Inrc   //where可选参数 21
	Select column_name1,column_name2... From table_name Where col_name Between[value1,value2] Order By col_name Desc\Inrc   22
	Select column_name1,column_name2... From table_name Where col_name Like[value] Order By col_name Desc\Inrc  23
	
*/

void get_gram(string single[], int len)
{
	//string keyword[32]={"int", "float", "text", "create","use","table","database","_databases","alter","truncate",\
	//"add","column","drop","rename","select","update","delete","insert","into","set","values","show",\
	//"where","order","from","and","or","desc","incr","by","like","between"};
	string _int = "int";
	string _float = "float";
	string _text = "text";
	string _create = "create";
	string _use = "use";
	string _table = "table";
	string _database = "database";
	string _databases = "databases";
	string _alter = "alter";
	string _truncate = "truncate";
	string _add = "add";
	string _column = "column";
	string _drop = "drop";
	string _rename = "rename";
	string _select = "select";
	string _update = "update";
	string _delete = "delete";
	string _insert = "insert";
	string _into = "into";
	string _set = "set";
	string _values = "values";
	string _show = "show";
	string _where = "where";
	string _order = "order";
	string _from = "from";
	string _and = "and";
	string _or = "or";
	string _desc = "desc";
	string _incr = "incr";
	string _by = "by";
	string _like = "like";
	string _between = "between";
//create
	if(len == 3 && 0 == _stricmp(single[0].c_str(), _create.c_str()) && 0 == _stricmp(single[1].c_str(), _database.c_str()))
		gram = 1;
	else if(0 == _stricmp(single[0].c_str(), _create.c_str()) && 0 == _stricmp(single[1].c_str(), _table.c_str()))
		gram = 2;
//alter
	else if((len == 5 || len == 6 ) && 0 == _stricmp(single[0].c_str(), _alter.c_str()) && 0 == _stricmp(single[1].c_str(), _table.c_str()) 
			&& 0 == _stricmp(single[3].c_str(), _add.c_str()))
		gram = 3;
	else if(len == 6 && 0 == _stricmp(single[0].c_str(), _alter.c_str()) && 0 == _stricmp(single[1].c_str(), _table.c_str()) 
			&& 0 == _stricmp(single[3].c_str(), _drop.c_str()) && 0 == _stricmp(single[4].c_str(), _column.c_str()))
		gram = 4;
	else if(len == 7 && 0 == _stricmp(single[0].c_str(), _alter.c_str()) && 0 == _stricmp(single[1].c_str(), _table.c_str()) 
			&& 0 == _stricmp(single[3].c_str(), _alter.c_str()) && 0 == _stricmp(single[4].c_str(), _column.c_str()))
		gram = 5;
//truncate
	else if(len == 3 && 0 == _stricmp(single[0].c_str(), _truncate.c_str()) && 0 == _stricmp(single[1].c_str(), _table.c_str()))
		gram = 6;
//use
	else if(len == 2 && 0 == _stricmp(single[0].c_str(), _use.c_str()))
		gram = 7;
//drop
	else if(len == 2 && 0 == _stricmp(single[0].c_str(), _drop.c_str()))
		gram = 8;
	else if(len == 3 && 0 == _stricmp(single[0].c_str(), _drop.c_str()))
		gram = 9;
//rename
	else if(len == 4 && 0 == _stricmp(single[0].c_str(), _rename.c_str()) && 0 == _stricmp(single[1].c_str(), _table.c_str()))
		gram = 10;
	else if(len == 4 && 0 == _stricmp(single[0].c_str(), _rename.c_str()) && 0 == _stricmp(single[1].c_str(), _database.c_str()))
		gram = 11;
//update
	else if(len >= 7 && 0 == _stricmp(single[0].c_str(), _update.c_str()) && 0 == _stricmp(single[2].c_str(), _set.c_str())
			&& is_contain(_where, single, len))
		gram = 12;
//delete
	else if(len == 7 && 0 == _stricmp(single[0].c_str(), _delete.c_str()) && 0 == _stricmp(single[1].c_str(), _from.c_str()) 
			&& 0 == _stricmp(single[3].c_str(), _where.c_str()))
		gram = 13;	
//insert
	else if(len >= 6 && 0 == _stricmp(single[0].c_str(), _insert.c_str()) && 0 == _stricmp(single[1].c_str(), _into.c_str()) 
			&& 0 == _stricmp(single[3].c_str(), _values.c_str()) && "(" == single[4])
		gram = 14;
	else if(len >= 8 && 0 == _stricmp(single[0].c_str(), _insert.c_str()) && 0 == _stricmp(single[1].c_str(), _into.c_str()) 
			&& "(" == single[3] && is_contain(_values, single, len))
		gram = 15;
//show
	else if(len >= 2 && 0 == _stricmp(single[0].c_str(), _show.c_str()) && 0 == _stricmp(single[1].c_str(), _databases.c_str()))
		gram = 16;
	else if(len >= 3 && 0 == _stricmp(single[0].c_str(), _show.c_str()) && 0 == _stricmp(single[2].c_str(), _table.c_str()))
		gram = 17;
	else if(len >= 2 && 0 == _stricmp(single[0].c_str(), _show.c_str()) && 0 == _stricmp(single[1].c_str(), _table.c_str()))
		gram = 18;
	else if(len >= 3 && 0 == _stricmp(single[0].c_str(), _show.c_str()) && 0 == _stricmp(single[2].c_str(), _column.c_str()))
		gram = 19;
//select
	else if(len >= 4 && 0 == _stricmp(single[0].c_str(), _select.c_str()) && is_contain(_from, single, len)
			&& !is_contain(_where, single, len) && !is_contain(_between, single, len) && !is_contain(_like, single, len))
		gram = 20;
	else if(len >= 8 && 0 == _stricmp(single[0].c_str(), _select.c_str()) && is_contain(_from, single, len) 
			&& is_contain(_where, single, len) && !is_contain(_between, single, len) && !is_contain(_like, single, len) 
			&& !is_contain(_and, single, len) && !is_contain(_or, single, len))
		gram = 21;
	else if(len >= 11 && 0 == _stricmp(single[0].c_str(), _select.c_str()) && is_contain(_from, single, len) 
			&& is_contain(_where, single, len) && is_contain(_between, single, len))
		gram = 22;
	else if(len >= 10 && 0 == _stricmp(single[0].c_str(), _select.c_str()) && is_contain(_from, single, len) 
			&& is_contain(_where, single, len) && is_contain(_like, single, len))
		gram = 23;
	else if(len >= 12 && 0 == _stricmp(single[0].c_str(), _select.c_str()) && is_contain(_from, single, len)
			&& is_contain(_where, single, len) && is_contain(_and, single, len))
		gram = 24;
	else if(len >= 12 && 0 == _stricmp(single[0].c_str(), _select.c_str()) && is_contain(_from, single, len)
			&& is_contain(_where, single, len) && is_contain(_or, single, len))
		gram = 25;

//error
	else
		gram = -1;
}

// 指定字符串数组中是否存在指定字符串, 不区分大小写，len为数组长度，存在则返回true，不存在返回false
bool is_contain(string str,string contain[], int len)
{
	int i;
	for(i=0; i<len; i++)
	{
		if( 0 == _stricmp(str.c_str(), contain[i].c_str()) )
		{
			return true;
		}
	}

	return false;
}

//检查小，中括号是否匹配, 检查关键字是否在一起
bool check_gram(string single[], int len)
{
	int i;
	int bracket1 = 0; // 小括号
	int bracket2 = 0; // 中括号

	for(i=0; i<len; i++)
	{
		if("=" == single[i] && ")" != single[i-1] && "(" != single[i+1])
			return false;
	}

	for(i=0; i<len; i++)
	{
		if(bracket1 < 0 || bracket2 < 0)
		{
			return false;
		}

		else if("(" == single[i])
		{
			bracket1++;
		}
		else if("[" == single[i])
		{
			bracket2++;
		}
		else if(")" == single[i])
		{
			bracket1--;
		}
		else if("]" == single[i])
		{
			bracket2--;
		}
		else
		{
			;
		}
	}

	if(0 != bracket1 || 0 != bracket2)
	{
		return false;
	}
	else{
		return true;
	}

	string _int = "int";
	string _float = "float";
	string _text = "text";
	string _create = "create";
	string _use = "use";
	string _table = "table";
	string _database = "database";
	string _databases = "databases";
	string _alter = "alter";
	string _truncate = "truncate";
	string _add = "add";
	string _column = "column";
	string _drop = "drop";
	string _rename = "rename";
	string _select = "select";
	string _update = "update";
	string _delete = "delete";
	string _insert = "insert";
	string _into = "into";
	string _set = "set";
	string _values = "values";
	string _show = "show";
	string _where = "where";
	string _order = "order";
	string _from = "from";
	string _and = "and";
	string _or = "or";
	string _desc = "desc";
	string _incr = "incr";
	string _by = "by";
	string _like = "like";
	string _between = "between";

	if(is_contain(_insert, single, len))
	{
		if( !is_contain(_into, single, len))
		{
			return false;
		}
	}

	if(is_contain(_create, single, len))
	{
		if( !(is_contain(_table, single, len) || is_contain(_database, single, len)))
		{
			return false;
		}
	}

	if(is_contain(_update, single, len))
	{
		if (!(is_contain(_set, single, len) && is_contain(_where, single, len)))
		{
			return false;
		}
	}

	if(is_contain(_delete, single, len))
	{
		if (!(is_contain(_from, single, len) && is_contain(_where, single, len)))
		{
			return false;
		}
	}

	return true;
}