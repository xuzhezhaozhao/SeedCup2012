#include"SeedCup.h"

//�½�һ�����ݿ�
int create_database(string & database_name)
{
	if(isExit_database(database_name))
	{
		cout << "error" << endl;
		return -1;
	}
	else if(iskeyword(database_name))
	{
		cout << "error" << endl;
		return -1;
	}
	else 
	{
		struct db new_db;
		new_db.db_name = database_name;
		all_db.push_back(new_db);
		return 0;
	}
}

//�ڵ�ǰ���ݿ��д�����,���ظ���ӡerror
int create_table(string & table_name)
{
	if(isExit_table(table_name))
	{
		cout << "error" << endl;
		return -1;
	}
	else if(iskeyword(table_name))
	{
		cout << "error" << endl;
		return -1;
	}
	else
	{
		struct table new_table;
		new_table.table_name = table_name;
		(*iter_current_db).db_c.push_back(new_table); // ������뵱ǰ���������ݿ���
		return 0;
	}
}

//����У�type�ֶα����е��������ͣ�0��NONE 1��int  2��float  3��string(��TEXT),������ظ���, ��������ֵ��Ϊ��
int create_column(string & table_name, string & column_name, int type)
{
	if(isExit_table(table_name))
	{
		if(isExit_column(table_name, column_name))
		{
			cout << "error" << endl;
			return -1;
		}
		else
		{
			int j;
			int count = 0; // ��¼�������Եĸ���
			list<table>::iterator iter = (*iter_current_db).db_c.begin(); // ָ����ָʾ��
			list<record>::iterator iter_record;
			iter = find_table(table_name);

			int int_count;
			int float_count;
			int str_count;

			for(j=0; j<50; j++)
			{
				if( (*iter).properity[j] != "")
				{
					count++;
				}
				else
					break;
			}

			(*iter).properity[count] = column_name;
			(*iter).col_type[count] = type;

			if((*iter).table_c.size() > 0)
			{
				iter_record = (*iter).table_c.begin();
				while(iter_record != (*iter).table_c.end())
				{
					switch(type)
					{
					case 0:
						break;
					case 1:
						int_count = get_int_count(iter, count);
						(*iter_record).int_x[int_count] = -65535;
						break;
					case 2:
						float_count = get_float_count(iter, count);
						(*iter_record).float_x[float_count] = -65535;
						break;
					case 3:
						str_count = get_str_count(iter, count);
						(*iter_record).string_x[str_count] = "#";
						break;
					default:
						break;
					}
					iter_record++;
				}
			}
		}
	}
	else
	{
		cout << "error" << endl;
		return -1;
	}
	return 0;
}