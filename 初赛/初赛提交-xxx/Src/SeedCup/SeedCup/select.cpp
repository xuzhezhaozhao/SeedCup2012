#include"SeedCup.h"

//select语句csv格式的显示数据，显示指定列col_name[]的全部记录，不包含where条件判断
int display_select_column(string & table_name, string col_name[])
{
	if(isExit_table(table_name))
	{
		if(isExit_column2(table_name, col_name))
		{
			int i, j;
			int count = 0; // 记录表中属性的个数
			if(isempty_table(table_name))
			{
				cout << "$" << endl;
				return -1;
			}
			else
			{
				list<table>::iterator iter = (*iter_current_db).db_c.begin(); // 指向表的指示器
				list<record>::iterator iter_record; // 指向记录

				for(i=0; i<(*iter_current_db).db_c.size(); i++) //遍历表
				{
					if(0 == _stricmp(table_name.c_str(), (*iter).table_name.c_str() )) //找到指定表
					{
						iter_record = (*iter).table_c.begin(); // 指向指定表的第一条记录

						for(j=0; j<(*iter).table_c.size(); j++)
						{
							display_select_record( table_name, col_name, iter_record);
							iter_record++;
						}
					}

					iter++;
				}

			}
			return 0;
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

/*
cmp: where表达式操作符 
 0: ==; 1: >; -1: <; 2: >=; -2: <=; 3： ~＝; 
order_by: 排序方式 
0: 升序; 1: 降序
*/
// 参数分别为：表名 选择列数组 比较列 比较值 比较类型 排序依据列 排序类型
int select_where_cmp(string & table_name, string select_col_name[], string & cmp_col_name, string & cmp_value, 
	int cmp, string & by_col_name, int order_by)
{
	if(isExit_table(table_name))
	{
		if(isExit_column2(table_name, select_col_name) && isExit_column(table_name, cmp_col_name))
		{
			list<table>::iterator iter;
			list<record>::iterator iter_record;

			if(isempty_table(table_name))
			{
				cout << "$" <<endl;
				return -1;
			}
			else
			{
				iter = find_table(table_name);
				iter_record = (*iter).table_c.begin(); //指向第一条记录

				int flag = 0;

			/*********** 先排序 *****************/
				if("" == by_col_name)
				{
					sort_table_default(table_name, select_col_name[0]); // 没有指定排序列默认以选择的第一列升序排列
				}

				else
				{
					if(isExit_column(table_name, by_col_name))
					{
						switch(order_by)
						{
						case 0:
							sort_table_incr(table_name, by_col_name);
							break;
						case 1:
							sort_table_desc(table_name, by_col_name);
							break;
						default:
							break;
						}
					}
					else
					{
						cout << "error" << endl;
						return -1;
					}
				}
			/**********************************/
				while(iter_record != (*iter).table_c.end())
				{
					if(where_cmp(iter,iter_record, cmp_col_name, cmp_value, cmp))
					{
						display_select_record(table_name, select_col_name, iter_record);
						flag = 1;
					}
					iter_record++;
				}

				if(0 == flag) // 没有符合条件的项
				{
					cout << "$" <<endl;
					return -1;
				}

			}
		}
		else
		{
			cout << "error" <<endl;
			return -1;
		}
	}
	else
	{
		cout << "error" <<endl;
		return -1;
	}
	return 0;
}

// 参数分别为：表名 选择列数组 比较列 比较值1 比较值2 排序依据列 排序类型
int select_where_between(string & table_name, string select_col_name[], string & bet_col_name, 
	string & bet_value1, string & bet_value2, string & by_col_name, int order_by)

{
	if(isExit_table(table_name))
	{
		if(isExit_column2(table_name, select_col_name) && isExit_column(table_name, bet_col_name))
		{
			list<table>::iterator iter;
			list<record>::iterator iter_record;
			if(isempty_table(table_name))
			{
				cout << "$" <<endl;
				return -1;
			}
			else
			{
				iter = find_table(table_name);
				iter_record = (*iter).table_c.begin(); //指向第一条记录

				int flag = 0;

			/*********** 先排序 *****************/
				if("" == by_col_name)
				{
					sort_table_incr(table_name, select_col_name[0]); // 没有指定排序列默认以选择的第一列升序排列
				}

				else
				{
					if(isExit_column(table_name, by_col_name))
					{
						switch(order_by)
						{
						case 0:
							sort_table_incr(table_name, by_col_name);
							break;
						case 1:
							sort_table_desc(table_name, by_col_name);
							break;
						default:
							break;
						}
					}
					else
					{
						cout << "error" << endl;
						return -1;
					}
				}
			/**********************************/

				while(iter_record != (*iter).table_c.end())
				{
					if( where_between(iter, iter_record, bet_col_name, bet_value1, bet_value2) )
					{
						display_select_record(table_name, select_col_name, iter_record);
						flag = 1;
					}
					iter_record++;
				}

				if(0 == flag) // 没有符合条件的项
				{
					cout << "$" <<endl;
					return -1;
				}

			}
			return 0;
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

//参数分别为：表名 选择列数组 比较列 比较值 排序依据列 排序类型
int select_where_like(string & table_name, string select_col_name[], string & like_col_name, 
	string & like_value, string & by_col_name, int order_by)
{
	if(isExit_table(table_name))
	{
		if(isExit_column2(table_name, select_col_name) && isExit_column(table_name, like_col_name))
		{
			list<table>::iterator iter;
			list<record>::iterator iter_record;
	
			if(isempty_table(table_name))
			{
				cout << "$" <<endl;
				return -1;
			}
			else
			{
				iter = find_table(table_name);
				iter_record = (*iter).table_c.begin(); //指向第一条记录

				int col_num = get_col_num(iter, like_col_name)-1;  // 得到行号，0起始

				int flag = 0;

			/*********** 先排序 *****************/
				if("" == by_col_name)
				{
					sort_table_incr(table_name, select_col_name[0]); // 没有指定排序列默认以选择的第一列升序排列
				}

				else
				{
					if(isExit_column(table_name, by_col_name))
					{
						switch(order_by)
						{
						case 0:
							sort_table_incr(table_name, by_col_name);
							break;
						case 1:
							sort_table_desc(table_name, by_col_name);
							break;
						default:
							break;
						}
					}
					else
					{
						cout << "error" << endl;
						return -1;
					}
				}
			/**********************************/
				while(iter_record != (*iter).table_c.end())
				{
					if(where_like(iter, iter_record, like_col_name, like_value))
					{
						display_select_record(table_name, select_col_name, iter_record);
						flag = 1;
					}

					iter_record++;
				}

				if(0 == flag) // 没有符合条件的项
				{
					cout << "$" <<endl;
					return -1;
				}
			}
		}
		else
		{
			cout << "error" <<endl;
			return -1;
		}
	}
	else
	{
		cout << "error" <<endl;
		return -1;
	}
	return 0;
}

//分别实现and和or操作符
int select_where_and(string & table_name, string select_col_name[], string & cmp_col_name1, string & cmp_value1, 
	int cmp1, string & cmp_col_name2, string & cmp_value2, int cmp2, string & by_col_name, int order_by)
{
	if(isExit_table(table_name))
	{
		if(isExit_column2(table_name, select_col_name) && isExit_column(table_name, cmp_col_name1) 
			&& isExit_column(table_name, cmp_col_name2))
		{
			list<table>::iterator iter;
			list<record>::iterator iter_record;
			if(isempty_table(table_name))
			{
				cout << "$" <<endl;
				return -1;
			}
			else
			{

			iter = find_table(table_name);
			iter_record = (*iter).table_c.begin(); //指向第一条记录

			int flag = 0;

		/*********** 先排序 *****************/
			if("" == by_col_name)
			{
				sort_table_incr(table_name, select_col_name[0]); // 没有指定排序列默认以选择的第一列升序排列
			}

			else
			{
				if(isExit_column(table_name, by_col_name))
				{
					switch(order_by)
					{
					case 0:
						sort_table_incr(table_name, by_col_name);
						break;
					case 1:
						sort_table_desc(table_name, by_col_name);
						break;
					default:
						break;
					}
				}
				else
				{
					cout <<"error"<<endl;
					return -1;
				}
			}
		/**********************************/
			while(iter_record != (*iter).table_c.end())
			{
				if(where_cmp(iter,iter_record, cmp_col_name1, cmp_value1, cmp1) && where_cmp(iter,iter_record, cmp_col_name2, cmp_value2, cmp2) )
				{
					display_select_record(table_name, select_col_name, iter_record);
					flag = 1;
				}
				iter_record++;
			}

			if(0 == flag) // 没有符合条件的项
			{
				cout << "$" <<endl;
				return -1;
			}

			}
			return 0;
		}
		else
		{
			cout << "error" <<endl;
			return -1;
		}
	}
	else
	{
		cout << "error" <<endl;
		return -1;
	}
}
int select_where_or(string & table_name, string select_col_name[], string & cmp_col_name1, string & cmp_value1, int cmp1, 
	string & cmp_col_name2, string & cmp_value2, int cmp2, string & by_col_name, int order_by)

{
	if(isExit_table(table_name))
	{
		if(isExit_column2(table_name, select_col_name) && isExit_column(table_name, cmp_col_name1) 
			&& isExit_column(table_name, cmp_col_name2))
		{
			list<table>::iterator iter;
			list<record>::iterator iter_record;
			if(isempty_table(table_name))
			{
				cout << "$" <<endl;
				return -1;
			}
			else
			{
			iter = find_table(table_name);
			iter_record = (*iter).table_c.begin(); //指向第一条记录

			int flag = 0;

		/*********** 先排序 *****************/
			if("" == by_col_name)
			{
				sort_table_default(table_name, select_col_name[0]); // 没有指定排序列默认以选择的第一列升序排列
			}

			else
			{
				if(isExit_column(table_name, by_col_name))
				{
					switch(order_by)
					{
					case 0:
						sort_table_incr(table_name, by_col_name);
						break;
					case 1:
						sort_table_desc(table_name, by_col_name);
						break;
					default:
						break;
					}
				}
				else
				{
					cout << "error" << endl;
					return -1;
				}
			}
		/**********************************/
			while(iter_record != (*iter).table_c.end())
			{
				if(where_cmp(iter,iter_record, cmp_col_name1, cmp_value1, cmp1) || \
					where_cmp(iter,iter_record, cmp_col_name2, cmp_value2, cmp2) )
				{
					display_select_record(table_name, select_col_name, iter_record);
					flag = 1;
				}
				iter_record++;
			}

			if(0 == flag) // 没有符合条件的项
			{
				cout << "$" <<endl;
				return -1;
			}

			}
			return 0;
		}
		else
		{
			cout << "error" <<endl;
			return -1;
		}
	}
	else
	{
		cout << "error" <<endl;
		return -1;
	}
}