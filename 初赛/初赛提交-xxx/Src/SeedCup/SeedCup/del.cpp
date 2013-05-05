#include"SeedCup.h"


//���ָ�����ݿ������б�������Ľṹ�����������, �ɹ�Ϊ1�����ɹ�����0
int truncate_database(string & database_name)
{
	if(isExit_database(database_name))
	{
		int i, j;

		list<db>::iterator iter = all_db.begin();
		list<table>::iterator iter_table;
	
		for(i=0; i<all_db.size(); i++)
		{
			if(0 == _stricmp( database_name.c_str(), (*iter).db_name.c_str() ) ) //�ҵ�ָ�����ݿ�
			{
				iter_table = (*iter).db_c.begin();   //ָ����е�һ�ű�
				for(j=0; j<(*iter).db_c.size(); j++)   //����ÿ�ű�
				{
					(*iter_table).table_c.clear(); // ������������

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

//���ָ����������Ľṹ�����������, �ɹ�Ϊ1�����ɹ�����0
int truncate_table(string & table_name)
{
	if(isExit_table(table_name))
	{
		list<table>::iterator iter_table = find_table(table_name);
		(*iter_table).table_c.clear(); // ������������
		return 0;
	}
	else
	{
		cout << "error" <<endl;
		return -1;
	}
}

//ɾ�����ݿ⣬�ɹ�1��ʧ��0
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
				if(0 == _stricmp(database_name.c_str(), (*iter_current_db).db_name.c_str())) // ɾ�����ǵ�ǰ��
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

//ɾ��ָ������ָ����
int drop_table(string & database_name, string & table_name)
{
	int i, j;
	list<db>::iterator iter = all_db.begin();
	list<table>::iterator iter_table;

	for(i=0; i<all_db.size(); i++)
	{
		if(0 == _stricmp( database_name.c_str(), (*iter).db_name.c_str() ) ) //�ҵ�ָ����
		{
			iter_table = (*iter).db_c.begin();  //ָ�����ݿ��е�һ�ű�
			for(j=0; j<(*iter).db_c.size(); j++) // �������ݿ��еı�
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

//ɾ���У��ɹ�����1��ʧ��0
int delete_column(string & table_name, string & column_name)
{
	int i, j, k;
	int count = 0; // ��¼�������Եĸ���
	int int_count = 0;
	int float_count = 0;
	int str_count = 0;

	list<table>::iterator iter = (*iter_current_db).db_c.begin(); // ָ����ָʾ��
	list <record>::iterator iter_record; //ָ���¼��ָʾ��

	for(i=0; i<(*iter_current_db).db_c.size(); i++) //������
	{
		if(0 == _stricmp(table_name.c_str(), (*iter).table_name.c_str() )) // �ҵ�ָ����
		{
			iter_record = (*iter).table_c.begin();  //ָ���һ����¼
			count = column_count(iter);

			for(i=0; i<count; i++)
			{
				if(0 == _stricmp(column_name.c_str(), (*iter).properity[i].c_str()) ) // �ҵ�ָ����
				{
					switch( (*iter).col_type[i] ) // �鿴�е���������
					{
					case 0:
						break;
					case 1:
						int_count=get_int_count(iter, i);
						
						for(k=0; k<(*iter).table_c.size(); k++)
						{
							for(j=int_count; j<count-1; j++)
							{
								(*iter_record).int_x[j] = (*iter_record).int_x[j+1]; //ɾ����һ������	
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

//ɾ�����е�ָ����¼��ֻʵ����>,=,<֮��������
void delete_record(string & table_name, string & col_name, string & value, int cmp)	
{
	list<table>::iterator iter = find_table(table_name);
	list <record>::iterator iter_record = (*iter).table_c.begin(); //ָ���¼
	
	int count = column_count(iter);  // ����

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