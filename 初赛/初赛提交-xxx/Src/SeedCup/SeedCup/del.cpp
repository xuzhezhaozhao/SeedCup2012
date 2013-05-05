#include"SeedCup.h"


//清空指定数据库中所有表，保留表的结构，仅清空数据, 成功为1，不成功返回0
int truncate_database(string & database_name)
{
	if(isExit_database(database_name))
	{
		int i, j;

		list<db>::iterator iter = all_db.begin();
		list<table>::iterator iter_table;
	
		for(i=0; i<all_db.size(); i++)
		{
			if(0 == _stricmp( database_name.c_str(), (*iter).db_name.c_str() ) ) //找到指定数据库
			{
				iter_table = (*iter).db_c.begin();   //指向库中第一张表
				for(j=0; j<(*iter).db_c.size(); j++)   //遍历每张表
				{
					(*iter_table).table_c.clear(); // 将表的内容清空

					iter_table++;
				}

				return 1;
			}

			iter++;
		}
		return 0;
	}
	else
	{
		cout << "error" << endl;
		return -1;
	}
}

//清空指定表，保留表的结构，仅清空数据, 成功为1，不成功返回0
int truncate_table(string & table_name)
{
	if(isExit_table(table_name))
	{
		list<table>::iterator iter_table = find_table(table_name);
		(*iter_table).table_c.clear(); // 将表的内容清空
		return 0;
	}
	else
	{
		cout << "error" <<endl;
		return -1;
	}
}

//删除数据库，成功1，失败0
int drop_database(string & database_name)
{
	if(isExit_database(database_name))
	{
		int i;
		list<db>::iterator iter = all_db.begin();

		for(i=0; i<all_db.size(); i++)
		{
			if(0 == _stricmp( database_name.c_str(), (*iter).db_name.c_str() ) )
			{
				if(0 == _stricmp(database_name.c_str(), (*iter_current_db).db_name.c_str())) // 删除的是当前表
				{
					all_db.erase(iter);
					isUse = false;
					return 1;
				}
			}
		
			iter++;
		}

		return 0;
	}
	else
	{
		cout << "error" <<endl;
		return 0;
	}
}

//删除指定库中指定表
int drop_table(string & database_name, string & table_name)
{
	int i, j;
	list<db>::iterator iter = all_db.begin();
	list<table>::iterator iter_table;

	for(i=0; i<all_db.size(); i++)
	{
		if(0 == _stricmp( database_name.c_str(), (*iter).db_name.c_str() ) ) //找到指定库
		{
			iter_table = (*iter).db_c.begin();  //指向数据库中第一张表
			for(j=0; j<(*iter).db_c.size(); j++) // 遍历数据库中的表
			{
				if(0 == _stricmp( table_name.c_str(), (*iter_table).table_name.c_str() ))
				{
					(*iter).db_c.erase(iter_table);
					return 1;
				}
				iter_table++;
			}
		}
		iter++;
	}

	return 0;
}

//删除列，成功返回1，失败0
int delete_column(string & table_name, string & column_name)
{
	int i, j, k;
	int count = 0; // 记录表中属性的个数
	int int_count = 0;
	int float_count = 0;
	int str_count = 0;

	list<table>::iterator iter = (*iter_current_db).db_c.begin(); // 指向表的指示器
	list <record>::iterator iter_record; //指向记录的指示器

	for(i=0; i<(*iter_current_db).db_c.size(); i++) //遍历表
	{
		if(0 == _stricmp(table_name.c_str(), (*iter).table_name.c_str() )) // 找到指定表
		{
			iter_record = (*iter).table_c.begin();  //指向第一条记录
			count = column_count(iter);

			for(i=0; i<count; i++)
			{
				if(0 == _stricmp(column_name.c_str(), (*iter).properity[i].c_str()) ) // 找到指定列
				{
					switch( (*iter).col_type[i] ) // 查看列的数据类型
					{
					case 0:
						break;
					case 1:
						int_count=get_int_count(iter, i);
						
						for(k=0; k<(*iter).table_c.size(); k++)
						{
							for(j=int_count; j<count-1; j++)
							{
								(*iter_record).int_x[j] = (*iter_record).int_x[j+1]; //删除这一列数据	
							}
							iter_record++;
						}
						break;
					case 2:
						for(j=0; j<i; j++)
						{
							if( 2 == (*iter).col_type[j])
							{
								float_count++;
							}
						}

						for(k=0; k<(*iter).table_c.size(); k++)
						{
							for(j=float_count; j<count-1; j++)
							{
								(*iter_record).float_x[j] = (*iter_record).float_x[j+1];
							}	
							iter_record++;
						}
						break;
					case 3:
						for(j=0; j<i; j++)
						{
							if( 3 == (*iter).col_type[j])
							{
								str_count++;
							}
						}

						for(k=0; k<(*iter).table_c.size(); k++)
						{
							for(j=str_count; j<count-1; j++)
							{
								(*iter_record).string_x[j] = (*iter_record).string_x[j+1];	
							}
							iter_record++;
						}
						break;
					default:
						break;
					}

					for(k=i; k<count-1; k++)
					{
						(*iter).properity[k] = (*iter).properity[k+1];
						(*iter).col_type[k] = (*iter).col_type[k+1];
					}
					(*iter).properity[k] = "";

					return 1;
				}
			}
		}

		iter++;
	}

	return 0;
}

//删除表中的指定记录，只实现了>,=,<之类的运算符
void delete_record(string & table_name, string & col_name, string & value, int cmp)	
{
	list<table>::iterator iter = find_table(table_name);
	list <record>::iterator iter_record = (*iter).table_c.begin(); //指向记录
	
	int count = column_count(iter);  // 列数

	while(iter_record != (*iter).table_c.end())
	{
		if(where_cmp(iter, iter_record, col_name, value, cmp))
		{
			iter_record = (*iter).table_c.erase(iter_record);
		}
		else
		{
			iter_record++;
		}
	}
}