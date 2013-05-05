#include"SeedCup.h"

int execute_file(string input_file)
{
	int count;
	int i;
	
	char temp[1000];
	string command[255];
	count = 0;
	ifstream fin(input_file, ifstream::in);

	while(!fin.eof())
	{
		fin.getline(temp,1000,';');
		command[count] = temp;
		count++;
	}
	for(i=0; i<count-1; i++)
	{
		execute(command[i]);
		//cout << gram << endl; // for debug
	}
	return 0;
}

//执行一条命令
void execute(string line)
{

	int len;
	string single[255];	
	divider = false;  // 初始时除数不为08
	math_to(line);
	if(!divider)  // 如果除数不为0
	{
		len = covert_sentence(line, single);	
		if(check_gram(single, len))
		{
			get_gram(single, len);
			exe_commands(single, len);
		}
		else
		{
			cout << "error" << endl;
		}
	}
	else  // 除数为0
	{
		cout << "error" << endl;
	}
}

//根据解析出来的语法调用相应的操作函数
int exe_commands(string single[], int len) // 命令字符串数组及长度
{
	int i, j;
	string col_update[10] = {""};
	string value_update[10] = {""};
	string col_name_update = "";
	string col_value_update = "";

	string insert_col[20] = {""};
	string insert_value[20] = {""};

	string select_col_name[20] = {""};
	string select_table = "";
	string by_col_name = "";

	string bet_col_name = "";
	string bet_value1 = "";
	string bet_value2 = "";

	string like_value = "";
	string like_col_name = "";

	string and_col_name1 = "";
	string and_col_name2 = "";
	string and_value1 = "";
	string and_value2 = "";
	int and_cmp1;
	int and_cmp2;

	string or_col_name1 = "";
	string or_col_name2 = "";
	string or_value1 = "";
	string or_value2 = "";
	int or_cmp1;
	int or_cmp2;

	list<table>::iterator iter_table;

	switch(gram)
	{
//create
	case 1:  // Create Database database_name  建库   1
		create_database(single[2]); 
		break;
	case 2: // Create Table table_name (column1 INT, column2 FLOAT, column3 TEXT)  建表
	if(isUse)
	{
		if(len == 5)
		{			
			create_table(single[2]);
		}
		else if(len > 5)
		{
			if(0 == create_table(single[2]))  // 建表的函数中有打印error了
			{
				for(i=4; i<len-1; i++)
				{
					if(0 == _stricmp(single[i+1].c_str(), "int"))
					{
						create_column(single[2], single[i], 1);
						i=i+1;  // 往后偏移一个
					}
					else if(0 == _stricmp(single[i+1].c_str(), "float"))
					{
						create_column(single[2], single[i], 2);
						i=i+1;
					}
					else if(0 == _stricmp(single[i+1].c_str(), "text"))
					{
						create_column(single[2], single[i], 3);
						i=i+1;
					}
					else
					{
						create_column(single[2], single[i], 0);
					}
				}
				return 0;
			}
			else
				return -1;   // 建表的函数中有打印error了
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
		break;

//Alter Table:
	case 3:  // Alter Table table_name Add column_name  INT 添加列   3
	if(isUse)
	{
		if(0 == _stricmp(single[5].c_str(), "int"))
		{
			create_column(single[2], single[4], 1);
		}
		else if(0 == _stricmp(single[5].c_str(), "float"))
		{
			create_column(single[2], single[4], 2);
		}
		else if(0 == _stricmp(single[5].c_str(), "text"))
		{
			create_column(single[2], single[4], 3);
		}
		else
		{
			create_column(single[2], single[4], 0);
		}
	}
	else
	{
		cout << "error" << endl;
		return -1;
	}
		break;
	case 4: //Alter Table table_name Drop Column column_name 删除列 4
	if(isUse)
	{
		delete_column(single[2], single[5]);
		break;
	case 5:  //Alter Table table_name Alter Column column_name INT  修改列数据类型 5
		if(0 == _stricmp(single[6].c_str(), "int"))
		{
			retype_column(single[2], single[5], 1);
		}
		else if(0 == _stricmp(single[6].c_str(), "float"))
		{
			retype_column(single[2], single[5], 2);
		}
		else if(0 == _stricmp(single[6].c_str(), "text"))
		{
			retype_column(single[2], single[5], 3);
		}
		else
		{
			cout << "error" << endl;   //修改数据类型为NONE
			return -1;
		}
	}
	else
	{
		cout << "error" <<endl;
		return -1;
	}
		break;

//Truncate:
	case 6:   //Truncate Table table_name   //保留结构   6
	if(isUse)
	{
		truncate_table(single[2]);
	}
	else
	{
		cout <<"error" << endl;
		return -1;
	}
		break;

//Use:
	case 7:   //Use database_name //使用数据库   7
	if(isExit_database(single[1]))
	{
		use_database(single[1]);
		isUse = true;
	}
	else
	{
		cout << "error" << endl;
		return -1;
	}
		break;

//Drop:
	case 8:   //Drop database_name  // 删除库   8
	if(isExit_database(single[1]))
	{
		drop_database(single[1]);
	}
	else
	{
		cout << "error" << endl;
		return -1;
	}
		break;
	case 9:  //Drop database_name table_name //删除表   9
	if(isExit_database(single[1]))
	{
		if(isExit_table2(single[1], single[2]))
		{
			drop_table(single[1], single[2]);
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
		break;

//Rename:
	case 10:  //Rename Table old_name new_name // 重命名表  10
	if(isUse)
	{
		if(isExit_table(single[2]))
		{
			rename_table(single[2], single[3]);
		}
		else
		{
			cout << "error" << endl;
			return -1;
		}
	}
	else
	{
		cout<<"error"<<endl;
		return -1;
	}
		break;
	case 11:  //Rename Database old_name new_name //重命名库  11
		if(isExit_database(single[2]))
		{
			rename_database(single[2], single[3]);
		}
		else
		{
			cout << "error" << endl;
			return -1;
		}
		break;

//Update:
	case 12: //Update table_name Set (col1,col2,...)=(new_value1,new_value2,...) Where col_name==old_value // 修改表中数据   12 
		//void update_table(string & table_name, string & col_name, string & value, 
		//	string col_update[], string value_update[], int cmp);
	if(isUse)
	{
		j = 0;
		for(i=4; i<len; i++)
		{
			if(single[i] != ")")
			{
				col_update[j] = single[i];
				j++;
			}
			else
				break;
		}
		col_update[j] = "";

		i = i+3;  //偏移到第一个值
		j = 0;

		for(; i<len; i++)
		{
			if(single[i] != ")")
			{
				value_update[j] = single[i];
				j++;
			}
			else
				break;
		}
		value_update[j] = "";
		col_name_update = single[i+2];
		col_value_update = single[i+4];

		if(isExit_table(single[1])) 
		{
			if(isExit_column(single[1], col_name_update) && isExit_column2(single[1], col_update))
			{
				if("==" == single[i+3])
					update_table(single[1], col_name_update, col_value_update, col_update, value_update, 0);
				else if(">" == single[i+3])
					update_table(single[1], col_name_update, col_value_update, col_update, value_update, 1);
				else if("<" == single[i+3])
					update_table(single[1], col_name_update, col_value_update, col_update, value_update, -1);
				else if(">=" == single[i+3])
					update_table(single[1], col_name_update, col_value_update, col_update, value_update, 2);
				else if("<=" == single[i+3])
					update_table(single[1], col_name_update, col_value_update, col_update, value_update, -2);
				else if("~=" == single[i+3])
					update_table(single[1], col_name_update, col_value_update, col_update, value_update, 3);
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
		break;

//Delete:
	case 13:   //Delete From table_name Where col_name == value  //删除表中部分数据   13
	if(isUse)
	{
		if(isExit_table(single[2]))
		{
			if(isExit_column(single[2], single[4]))
			{
				if("==" == single[5])
				{
					delete_record(single[2], single[4], single[6], 0);
				}
				else if(">" == single[5])
				{
					delete_record(single[2], single[4], single[6], 1);
				}
				else if("<" == single[5])
				{
					delete_record(single[2], single[4], single[6], -1);
				}
				else if(">=" == single[5])
				{
					delete_record(single[2], single[4], single[6], 2);
				}
				else if("<=" == single[5])
				{
					delete_record(single[2], single[4], single[6], -2);
				}
				else if("~=" == single[5])
				{
					delete_record(single[2], single[4], single[6], 3);
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
		break;

//Insert:
	case 14: //Insert Into table_name Values(value1, value2,...) //添加记录 14
	if(isUse)
	{ 
		j = 0;
		for(i=5; i<len; i++)
		{
			if(")" != single[i])
			{
				insert_value[j] = single[i];	
				j++;
			}
			else
				break;	
		}
		if(isExit_table(single[2]))
		{
			add_record(single[2], insert_value);
		}
		else
		{
			cout << "error" << endl;
			return -1;
		}
		break;
	}
	else
	{
		cout << "error" << endl;
		return -1;
	}
	case 15: 
	if(isUse)
	{
		//Insert Into talbe_name (col1, col2, ...) Values(value1, value2,...)  // value可以为空，用逗号分隔，(, 'yao',,'wuhan')  15
		j = 0;
		for(i=4; i<len; i++)
		{
			if(")" != single[i])
			{
				insert_col[j] = single[i];	
				j++;
			}
			else
				break;	
		}
		insert_col[j] = "";
		i = i+3;
		j = 0;
		for(; i<len; i++)
		{
			if(")" != single[i])
			{
				insert_value[j] = single[i];	
				j++;
			}
			else
				break;	
		}
		insert_value[j] = "";
		if(isExit_table(single[2]))
		{
			if(isExit_column2(single[2], insert_col))
			{
				add_record2(single[2], insert_col, insert_value);
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
	}
	else
	{
		cout << "error" << endl;
		return -1;
	}
		break;

//Show:
	case 16: //Show DatabaseS Order By DESC\Incr  // 打印所有的库  16
		if(2 == len)
		{
			show_database(-1);
		}
		else if(4 == len || 5 == len)
		{
			if(0 == _stricmp(single[4].c_str(), "desc"))
				show_database(1);
			else if(0 == _stricmp(single[4].c_str(), "incr"))
				show_database(0);
			else
			{
				show_database(0);
			}
		}
		else
		{
			cout << "error" << endl;
			return -1;
		}
		break;
	case 17: // Show database_name Table Order By DESC\INCR   //打印指定库的表 17
		if(isExit_database(single[1]))
		{
			if(3 == len)
			{
				show_table(single[1], -1);
			}
			else if(6 == len || 5 == len)
			{
				if(0 == _stricmp(single[5].c_str(), "desc"))
					show_table(single[1], 1);
				else if(0 == _stricmp(single[5].c_str(), "incr"))
					show_table(single[1], 0);
				else
				{
					show_table(single[1], 0);
				}
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
		break;
	case 18: //Show Table Order By Desc\Incr // 打印当前数据库中的表  18
	if(isUse)
	{
		if(2 == len)
		{
			show_table((*iter_current_db).db_name, -1);
		}
		else if(4 == len || 5 == len)
		{
			if(0 == _stricmp(single[4].c_str(), "desc"))
				show_table((*iter_current_db).db_name, 1);
			else if(0 == _stricmp(single[4].c_str(), "incr"))
				show_table((*iter_current_db).db_name, 0);
			else
			{
				show_table((*iter_current_db).db_name, 0);
			}
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
		break;
	case 19: //Show table_name Column Order By DESC\Incr  //打印指定表的所有列 19
	if(isUse)
	{
		if(isExit_table(single[1]))
		{
			if(3 == len)
			{
				show_column((*iter_current_db).db_name, single[1], -1);
			}
			else if(6 == len || 5 == len)
			{
				if(0 == _stricmp(single[5].c_str(), "desc"))
					show_column((*iter_current_db).db_name, single[1], 1);
				else if(0 == _stricmp(single[5].c_str(), "incr"))
					show_column((*iter_current_db).db_name, single[1], 0);
				else
				{
					show_column((*iter_current_db).db_name, single[1], 0);
				}
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
	}
	else
	{
		cout << "error" << endl;
		return -1;
	}
		break;

//select:
	case 20:  //Select column_name1,column_name2... From table_name Order By col_name Desc\Inrc    //order by 为可选参数，不选默认为升序 20
	if(isUse)
	{
		if("*"  != single[1])
		{
			j = 0;
			for(i=1; i<len; i++)
			{
				if(0 != _stricmp(single[i].c_str(), "from"))
				{
					select_col_name[j] = single[i];
					j++;
				}
				else
					break;
			}
			select_col_name[j] = "";
			select_table = single[i+1];
		}
		else
		{
			select_table = single[3];
			if(isExit_table(single[3]))
			{
				iter_table = find_table(select_table);
				i = 0;
				while("" != (*iter_table).properity[i])
				{
					select_col_name[i] = (*iter_table).properity[i];
					i++;
				}
				select_col_name[i] = "";
				i = 2;
			}
			else
			{
				cout << "error" << endl;
				return -1;
			}
		}
		if(isExit_table(select_table))
		{
			if(isExit_column2(select_table, select_col_name))
			{
				if(0 != _stricmp(single[i+2].c_str(), "order"))
				{
					sort_table_default(select_table, select_col_name[0]);
					display_select_column(select_table, select_col_name);
				}
				else if(isExit_column(select_table, single[i+4]) && 0 == _stricmp(single[i+2].c_str(), "order") && 0 == _stricmp(single[i+5].c_str(), "desc"))
				{
					sort_table_desc(select_table, single[i+4]);
					display_select_column(select_table, select_col_name);
				}
				else if(isExit_column(select_table, single[i+4]) && 0 == _stricmp(single[i+2].c_str(), "order") && 0 == _stricmp(single[i+5].c_str(), "incr"))
				{
					sort_table_incr(select_table, single[i+4]);
					display_select_column(select_table, select_col_name);
				}
				else if(isExit_column(select_table, single[i+4]) && 0 == _stricmp(single[i+2].c_str(), "order"))
				{
					sort_table_incr(select_table, single[i+4]);
					display_select_column(select_table, select_col_name);
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
		break;
	case 21: //Select column_name1, column_name2... From table_name Where cmp_col_name >= cmp_value Order By col_name Desc\Inrc   //where可选参数 21
	if(isUse)
	{
		if("*"  != single[1])
		{
			j = 0;
			for(i=1; i<len; i++)
			{
				if(0 != _stricmp(single[i].c_str(), "from"))
				{
					select_col_name[j] = single[i];
					j++;
				}
				else
					break;
			}
			select_col_name[j] = "";
			select_table = single[i+1];
		}
		else
		{
			select_table = single[3];
			if(isExit_table(select_table))
			{
				iter_table = find_table(select_table);
				i = 0;
				while("" != (*iter_table).properity[i])
				{
					select_col_name[i] = (*iter_table).properity[i];
					i++;
				}
				select_col_name[i] = "";
				i = 2;
			}
			else
			{
				cout << "error" << endl;
				return -1;
			}
		}
		if(isExit_table(select_table))
		{

			if(0 == _stricmp(single[i+2].c_str(), "where"))
			{
				if(isExit_column2(select_table, select_col_name))
				{
					if("==" == single[i+4])
					{
						if(0 != _stricmp(single[i+6].c_str(), "order"))
						{
							by_col_name = "";
							select_where_cmp(select_table, select_col_name, single[i+3], single[i+5], 0, by_col_name, 0);
						}
						else if(isExit_column(select_table, single[i+8]) && 0 == _stricmp(single[i+9].c_str(), "desc"))
						{
							by_col_name = single[i+8];
							select_where_cmp(select_table, select_col_name, single[i+3], single[i+5], 0, by_col_name, 1);
						}
						else if(isExit_column(select_table, single[i+8]) && 0 == _stricmp(single[i+9].c_str(), "incr"))
						{
							by_col_name = single[i+8];
							select_where_cmp(select_table, select_col_name, single[i+3], single[i+5], 0, by_col_name, 0);
						}
						else if(isExit_column(select_table, single[i+8]))
						{
							by_col_name = single[i+8];
							select_where_cmp(select_table, select_col_name, single[i+3], single[i+5], 0, by_col_name, 0);
						}
						else
						{
							cout << "error" << endl;
							return -1;
						}
					}
					else if(">" == single[i+4])
					{
						if(0 != _stricmp(single[i+6].c_str(), "order"))
						{
							by_col_name = "";
							select_where_cmp(select_table, select_col_name, single[i+3], single[i+5], 1, by_col_name, 0);
						}
						else if(isExit_column(select_table, single[i+8]) && 0 == _stricmp(single[i+9].c_str(), "desc"))
						{
							by_col_name = single[i+8];
							select_where_cmp(select_table, select_col_name, single[i+3], single[i+5], 1, by_col_name, 1);
						}
						else if(isExit_column(select_table, single[i+8]) && 0 == _stricmp(single[i+9].c_str(), "incr"))
						{
							by_col_name = single[i+8];
							select_where_cmp(select_table, select_col_name, single[i+3], single[i+5], 1, by_col_name, 0);
						}
						else if(isExit_column(select_table, single[i+8]))
						{
							by_col_name = single[i+8];
							select_where_cmp(select_table, select_col_name, single[i+3], single[i+5], 1, by_col_name, 0);
						}
						else
						{
							cout << "error" << endl;
							return -1;
						}
					}
					else if("<" == single[i+4])
					{
						if(0 != _stricmp(single[i+6].c_str(), "order"))
						{
							by_col_name = "";
							select_where_cmp(select_table, select_col_name, single[i+3], single[i+5], -1, by_col_name, 0);
						}
						else if(isExit_column(select_table, single[i+8]) && 0 == _stricmp(single[i+9].c_str(), "desc"))
						{
							by_col_name = single[i+8];
							select_where_cmp(select_table, select_col_name, single[i+3], single[i+5], -1, by_col_name, 1);
						}
						else if(isExit_column(select_table, single[i+8]) && 0 == _stricmp(single[i+9].c_str(), "incr"))
						{
							by_col_name = single[i+8];
							select_where_cmp(select_table, select_col_name, single[i+3], single[i+5], -1, by_col_name, 0);
						}
						else if(isExit_column(select_table, single[i+8]))
						{
							by_col_name = single[i+8];
							select_where_cmp(select_table, select_col_name, single[i+3], single[i+5], -1, by_col_name, 0);
						}
						else
						{
							cout << "error" << endl;
							return -1;
						}
					}
					else if(">=" == single[i+4])
					{
						if(0 != _stricmp(single[i+6].c_str(), "order"))
						{
							by_col_name = "";
							select_where_cmp(select_table, select_col_name, single[i+3], single[i+5], 2, by_col_name, 0);
						}
						else if(isExit_column(select_table, single[i+8]) && 0 == _stricmp(single[i+9].c_str(), "desc"))
						{
							by_col_name = single[i+8];
							select_where_cmp(select_table, select_col_name, single[i+3], single[i+5], 2, by_col_name, 1);
						}
						else if(isExit_column(select_table, single[i+8]) && 0 == _stricmp(single[i+9].c_str(), "incr"))
						{
							by_col_name = single[i+8];
							select_where_cmp(select_table, select_col_name, single[i+3], single[i+5], 2, by_col_name, 0);
						}
						else if(isExit_column(select_table, single[i+8]))
						{
							by_col_name = single[i+8];
							select_where_cmp(select_table, select_col_name, single[i+3], single[i+5], 2, by_col_name, 0);
						}

						else
						{
							cout << "error" << endl;
							return -1;
						}
					}
					else if("<=" == single[i+4])
					{
						if(0 != _stricmp(single[i+6].c_str(), "order"))
						{
							by_col_name = "";
							select_where_cmp(select_table, select_col_name, single[i+3], single[i+5], -2, by_col_name, 0);
						}
						else if(isExit_column(select_table, single[i+8]) && 0 == _stricmp(single[i+9].c_str(), "desc"))
						{
							by_col_name = single[i+8];
							select_where_cmp(select_table, select_col_name, single[i+3], single[i+5], -2, by_col_name, 1);
						}
						else if(isExit_column(select_table, single[i+8]) && 0 == _stricmp(single[i+9].c_str(), "incr"))
						{
							by_col_name = single[i+8];
							select_where_cmp(select_table, select_col_name, single[i+3], single[i+5], -2, by_col_name, 0);
						}
						else if(isExit_column(select_table, single[i+8]))
						{
							by_col_name = single[i+8];
							select_where_cmp(select_table, select_col_name, single[i+3], single[i+5], -2, by_col_name, 0);
						}
						else
						{
							cout << "error" << endl;
							return -1;
						}
					}
					else if("~=" == single[i+4])
					{
						if(0 != _stricmp(single[i+6].c_str(), "order"))
						{
							by_col_name = "";
							select_where_cmp(select_table, select_col_name, single[i+3], single[i+5], 3, by_col_name, 0);
						}
						else if(isExit_column(select_table, single[i+8]) && 0 == _stricmp(single[i+9].c_str(), "desc"))
						{
							by_col_name = single[i+8];
							select_where_cmp(select_table, select_col_name, single[i+3], single[i+5], 3, by_col_name, 1);
						}
						else if(isExit_column(select_table, single[i+8]) && 0 == _stricmp(single[i+9].c_str(), "incr"))
						{
							by_col_name = single[i+8];
							select_where_cmp(select_table, select_col_name, single[i+3], single[i+5], 3, by_col_name, 0);
						}
						else if(isExit_column(select_table, single[i+8]))
						{
							by_col_name = single[i+8];
							select_where_cmp(select_table, select_col_name, single[i+3], single[i+5], 3, by_col_name, 0);
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
		}
	}
	else
	{
		cout << "error" << endl;
		return -1;
	}
		break;
	case 22:  //Select column_name1,column_name2... From table_name Where col_name Between[value1,value2] Order By col_name Desc\Inrc   22
	if(isUse)
	{
		if("*"  != single[1])
		{
			j = 0;
			for(i=1; i<len; i++)
			{
				if(0 != _stricmp(single[i].c_str(), "from"))
				{
					select_col_name[j] = single[i];
					j++;
				}
				else
					break;
			}
			select_col_name[j] = "";
			select_table = single[i+1];
		}
		else
		{
			select_table = single[3];
			iter_table = find_table(select_table);
			i = 0;
			while("" != (*iter_table).properity[i])
			{
				select_col_name[i] = (*iter_table).properity[i];
				i++;
			}
			select_col_name[i] = "";
			i = 2;
		}	
		if(0 == _stricmp(single[i+2].c_str(), "where") && 0 == _stricmp(single[i+4].c_str(), "between"))
		{
			bet_col_name = single[i+3];
			bet_value1 = single[i+6];
			bet_value2 = single[i+7];
			if(0 != _stricmp(single[i+9].c_str(), "order"))
			{
				by_col_name = "";
				select_where_between(select_table,select_col_name,bet_col_name,bet_value1,bet_value2, by_col_name, 0);
			}
			else if(0 == _stricmp(single[i+9].c_str(), "order") && 0 == _stricmp(single[i+12].c_str(), "desc"))
			{
				by_col_name = single[i+11];
				select_where_between(select_table,select_col_name,bet_col_name,bet_value1,bet_value2, by_col_name, 1);
			}
			else if(0 == _stricmp(single[i+9].c_str(), "order") && 0 == _stricmp(single[i+12].c_str(), "incr"))
			{
				by_col_name = single[i+11];
				select_where_between(select_table,select_col_name,bet_col_name,bet_value1,bet_value2, by_col_name, 0);
			}
			else if(0 == _stricmp(single[i+9].c_str(), "order"))
			{
				by_col_name = single[i+11];
				select_where_between(select_table,select_col_name,bet_col_name,bet_value1,bet_value2, by_col_name, 0);
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
	}
	else
	{
		cout << "error" << endl;
		return -1;
	}
		break;
	case 23:  //Select column_name1,column_name2... From table_name Where col_name Like[value] Order By col_name Desc\Inrc  23
	if(isUse)
	{
		if("*"  != single[1])
		{
			j = 0;
			for(i=1; i<len; i++)
			{
				if(0 != _stricmp(single[i].c_str(), "from"))
				{
					select_col_name[j] = single[i];
					j++;
				}
				else
					break;
			}
			select_col_name[j] = "";
			select_table = single[i+1];
		}
		else
		{
			select_table = single[3];
			iter_table = find_table(select_table);
			i = 0;
			while("" != (*iter_table).properity[i])
			{
				select_col_name[i] = (*iter_table).properity[i];
				i++;
			}
			select_col_name[i] = "";
			i = 2;
		}			
		like_value = single[i+6];
		like_col_name = single[i+3];
		if(0 == _stricmp(single[i+2].c_str(), "where") && 0 == _stricmp(single[i+4].c_str(), "like"))
		{
			if(0 != _stricmp(single[i+8].c_str(), "order"))
			{
				by_col_name = "";
				select_where_like(select_table, select_col_name, like_col_name, like_value, by_col_name, 0);
			}
			else if(0 == _stricmp(single[i+8].c_str(), "order") && 0 == _stricmp(single[i+11].c_str(), "desc"))
			{
				by_col_name = single[i+10];
				select_where_like(select_table, select_col_name, like_col_name, like_value, by_col_name, 1);
			}
			else if(0 == _stricmp(single[i+8].c_str(), "order") && 0 == _stricmp(single[i+11].c_str(), "incr"))
			{
				by_col_name = single[i+10];
				select_where_like(select_table, select_col_name, like_col_name, like_value, by_col_name, 0);
			}
			else if(0 == _stricmp(single[i+8].c_str(), "order"))
			{
				by_col_name = single[i+10];
				select_where_like(select_table, select_col_name, like_col_name, like_value, by_col_name, 0);
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
	}
	else
	{
		cout << "error" << endl;
		return -1;
	}
		break;

	case 24:   //Select column_name1,column_name2... From table_name Where col_name1 > value1 And col_name2 < value2 Order By col_name Desc\Inrc  24 
	if(isUse)
	{
		if("*"  != single[1])
		{
			j = 0;
			for(i=1; i<len; i++)
			{
				if(0 != _stricmp(single[i].c_str(), "from"))
				{
					select_col_name[j] = single[i];
					j++;
				}
				else
					break;
			}
			select_col_name[j] = "";
			select_table = single[i+1];
		}
		else
		{
			select_table = single[3];
			iter_table = find_table(select_table);
			i = 0;
			while("" != (*iter_table).properity[i])
			{
				select_col_name[i] = (*iter_table).properity[i];
				i++;
			}
			select_col_name[i] = "";
			i = 2;
		} // 得到select_table和select_col_name, i指向from
		and_col_name1 = single[i+3];
		and_value1 = single[i+5];
		and_col_name2 = single[i+7];
		and_value2 = single[i+9];
		if("==" == single[i+4])
			and_cmp1 = 0;
		else if(">" == single[i+4])
			and_cmp1 = 1;
		else if("<" == single[i+4])
			and_cmp1 = -1;
		else if(">=" == single[i+4])
			and_cmp1 = 2;
		else if("<=" == single[i+4])
			and_cmp1 = -2;
		else if("~=" == single[i+4])
			and_cmp1 = 3;
		else
		{
			cout << "error" <<endl; //操作符不合法
			return -1;
		}

		if("==" == single[i+8])
			and_cmp2 = 0;
		else if(">" == single[i+8])
			and_cmp2 = 1;
		else if("<" == single[i+8])
			and_cmp2 = -1;
		else if(">=" == single[i+8])
			and_cmp2 = 2;
		else if("<=" == single[i+8])
			and_cmp2 = -2;
		else if("~=" == single[i+8])
			and_cmp2 = 3;
		else
		{
			cout << "error" <<endl; //操作符不合法
			return -1;
		}

		if(0 != _stricmp(single[i+10].c_str(), "order"))
		{
			by_col_name = "";
			select_where_and(select_table, select_col_name, and_col_name1, and_value1,and_cmp1, and_col_name2, and_value2, and_cmp2, by_col_name, 0);
		}
		else if(0 == _stricmp(single[i+13].c_str(), "desc"))
		{
			by_col_name = single[i+12];
			select_where_and(select_table, select_col_name, and_col_name1, and_value1,and_cmp1, and_col_name2, and_value2, and_cmp2, by_col_name, 1);
		}
		else if(0 == _stricmp(single[i+13].c_str(), "incr"))
		{
			by_col_name = single[i+12];
			select_where_and(select_table, select_col_name, and_col_name1, and_value1,and_cmp1, and_col_name2, and_value2, and_cmp2, by_col_name, 0);
		}
		else
		{
			by_col_name = single[i+12];
			select_where_and(select_table, select_col_name, and_col_name1, and_value1,and_cmp1, and_col_name2, and_value2, and_cmp2, by_col_name, 0);
		}
	}
	else
	{
		cout << "error" << endl;
		return -1;
	}
		break;

	case 25:    //Select column_name1,column_name2... From table_name Where col_name1 > value1 And col_name2 < value2 Order By col_name Desc\Inrc  24 
	if(isUse)
	{
		if("*"  != single[1])
		{
			j = 0;
			for(i=1; i<len; i++)
			{
				if(0 != _stricmp(single[i].c_str(), "from"))
				{
					select_col_name[j] = single[i];
					j++;
				}
				else
					break;
			}
			select_col_name[j] = "";
			select_table = single[i+1];
		}
		else
		{
			select_table = single[3];
			iter_table = find_table(select_table);
			i = 0;
			while("" != (*iter_table).properity[i])
			{
				select_col_name[i] = (*iter_table).properity[i];
				i++;
			}
			select_col_name[i] = "";
			i = 2;
		} // 得到select_table和select_col_name, i指向from
		or_col_name1 = single[i+3];
		or_value1 = single[i+5];
		or_col_name2 = single[i+7];
		or_value2 = single[i+9];
		if("==" == single[i+4])
			or_cmp1 = 0;
		else if(">" == single[i+4])
			or_cmp1 = 1;
		else if("<" == single[i+4])
			or_cmp1 = -1;
		else if(">=" == single[i+4])
			or_cmp1 = 2;
		else if("<=" == single[i+4])
			or_cmp1 = -2;
		else if("~=" == single[i+4])
			or_cmp1 = 3;
		else
		{
			cout << "error" <<endl; //操作符不合法
			return -1;
		}

		if("==" == single[i+8])
			or_cmp2 = 0;
		else if(">" == single[i+8])
			or_cmp2 = 1;
		else if("<" == single[i+8])
			or_cmp2 = -1;
		else if(">=" == single[i+8])
			or_cmp2 = 2;
		else if("<=" == single[i+8])
			or_cmp2 = -2;
		else if("~=" == single[i+8])
			or_cmp2 = 3;
		else
		{
			cout << "error" <<endl; //操作符不合法
			return -1;
		}

		if(0 != _stricmp(single[i+10].c_str(), "order"))
		{
			by_col_name = "";
			select_where_or(select_table, select_col_name, or_col_name1, or_value1,or_cmp1, or_col_name2, or_value2, or_cmp2, by_col_name, 0);
		}
		else if(0 == _stricmp(single[i+13].c_str(), "desc"))
		{
			by_col_name = single[i+12];
			select_where_or(select_table, select_col_name, or_col_name1, or_value1,or_cmp1, or_col_name2, or_value2, or_cmp2, by_col_name, 1);
		}
		else if(0 == _stricmp(single[i+13].c_str(), "incr"))
		{
			by_col_name = single[i+12];
			select_where_or(select_table, select_col_name, or_col_name1, or_value1,or_cmp1, or_col_name2, or_value2, or_cmp2, by_col_name, 0);
		}
		else
		{
			by_col_name = single[i+12];
			select_where_or(select_table, select_col_name, or_col_name1, or_value1,or_cmp1, or_col_name2, or_value2, or_cmp2, by_col_name, 0);
		}
	}
	else
	{
		cout << "error" << endl;
		return -1;
	}
		break;
//error
	case -1:
			cout << "error" << endl;
			return -1;
		break;
	}

	return 0;
}