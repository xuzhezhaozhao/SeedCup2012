#include"SeedCup.h"

//select���csv��ʽ����ʾ���ݣ���ʾָ����col_name[]��ȫ����¼��������where�����ж�
int display_select_column(string & table_name, string col_name[])
{
	if(isExit_table(table_name))
	{
		if(isExit_column2(table_name, col_name))
		{
			int i, j;
			int count = 0; // ��¼�������Եĸ���
			if(isempty_table(table_name))
			{
				cout << "$" << endl;
				return -1;
			}
			else
			{
				list<table>::iterator iter = (*iter_current_db).db_c.begin(); // ָ����ָʾ��
				list<record>::iterator iter_record; // ָ���¼

				for(i=0; i<(*iter_current_db).db_c.size(); i++) //������
				{
					if(0 == _stricmp(table_name.c_str(), (*iter).table_name.c_str() )) //�ҵ�ָ����
					{
						iter_record = (*iter).table_c.begin(); // ָ��ָ����ĵ�һ����¼

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
cmp: where���ʽ������ 
 0: ==; 1: >; -1: <; 2: >=; -2: <=; 3�� ~��; 
order_by: ����ʽ 
0: ����; 1: ����
*/
// �����ֱ�Ϊ������ ѡ�������� �Ƚ��� �Ƚ�ֵ �Ƚ����� ���������� ��������
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
				iter_record = (*iter).table_c.begin(); //ָ���һ����¼

				int flag = 0;

			/*********** ������ *****************/
				if("" == by_col_name)
				{
					sort_table_default(table_name, select_col_name[0]); // û��ָ��������Ĭ����ѡ��ĵ�һ����������
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

				if(0 == flag) // û�з�����������
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

// �����ֱ�Ϊ������ ѡ�������� �Ƚ��� �Ƚ�ֵ1 �Ƚ�ֵ2 ���������� ��������
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
				iter_record = (*iter).table_c.begin(); //ָ���һ����¼

				int flag = 0;

			/*********** ������ *****************/
				if("" == by_col_name)
				{
					sort_table_incr(table_name, select_col_name[0]); // û��ָ��������Ĭ����ѡ��ĵ�һ����������
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

				if(0 == flag) // û�з�����������
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

//�����ֱ�Ϊ������ ѡ�������� �Ƚ��� �Ƚ�ֵ ���������� ��������
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
				iter_record = (*iter).table_c.begin(); //ָ���һ����¼

				int col_num = get_col_num(iter, like_col_name)-1;  // �õ��кţ�0��ʼ

				int flag = 0;

			/*********** ������ *****************/
				if("" == by_col_name)
				{
					sort_table_incr(table_name, select_col_name[0]); // û��ָ��������Ĭ����ѡ��ĵ�һ����������
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

				if(0 == flag) // û�з�����������
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

//�ֱ�ʵ��and��or������
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
			iter_record = (*iter).table_c.begin(); //ָ���һ����¼

			int flag = 0;

		/*********** ������ *****************/
			if("" == by_col_name)
			{
				sort_table_incr(table_name, select_col_name[0]); // û��ָ��������Ĭ����ѡ��ĵ�һ����������
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

			if(0 == flag) // û�з�����������
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
			iter_record = (*iter).table_c.begin(); //ָ���һ����¼

			int flag = 0;

		/*********** ������ *****************/
			if("" == by_col_name)
			{
				sort_table_default(table_name, select_col_name[0]); // û��ָ��������Ĭ����ѡ��ĵ�һ����������
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

			if(0 == flag) // û�з�����������
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