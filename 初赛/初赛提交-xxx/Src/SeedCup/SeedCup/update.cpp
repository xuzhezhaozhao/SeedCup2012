#include"SeedCup.h"

//�޸�����������
int retype_column(string & table_name, string & col_name, int retype)
{
	if(isExit_table(table_name))
	{
		if(isExit_column(table_name, col_name))
		{
			int i;
			int col_count;
			int col_num;

			int int_count, int_count_all;
			int float_count, float_count_all;
			int str_count, str_count_all;

			char buf[50];
			list<table>::iterator iter;
			list<record>::iterator iter_record;
			iter = find_table(table_name);
			iter_record = (*iter).table_c.begin(); // ָ���һ����¼

			col_num = get_col_num(iter, col_name)-1;
			col_count = column_count(iter); //����

			switch((*iter).col_type[col_num])
			{
			case 0:
				switch(retype)
				{
				case 0:
					break;
				case 1:
					int_count = get_int_count(iter, col_num);
					int_count_all = get_int_count(iter, col_count);
					(*iter).col_type[col_num] = 1;
					while(iter_record != (*iter).table_c.end())
					{
						for(i=int_count_all; i>int_count; i++)
						{
							(*iter_record).int_x[i] = (*iter_record).int_x[i-1];
						}
						(*iter_record).int_x[int_count] = 0; //
						iter_record++;
					}
					break;
				case 2:
					float_count = get_float_count(iter, col_num); //
					float_count_all = get_float_count(iter, col_count);  //
					(*iter).col_type[col_num] = 2; //
					while(iter_record != (*iter).table_c.end()) 
					{
						for(i=float_count_all; i>float_count; i++)  //
						{
							(*iter_record).float_x[i] = (*iter_record).float_x[i-1]; //
						}
						(*iter_record).float_x[float_count] = 0; //
						iter_record++;
					}
					break;
				case 3:
					str_count = get_str_count(iter, col_num); //
					str_count_all = get_str_count(iter, col_count);  //
					(*iter).col_type[col_num] = 3; //
					while(iter_record != (*iter).table_c.end()) 
					{
						for(i=str_count_all; i>str_count; i++)  //
						{
							(*iter_record).string_x[i] = (*iter_record).string_x[i-1]; //
						}
						(*iter_record).string_x[str_count] = "#"; //
						iter_record++;
					}
					break;
				default:
					break;
				}
				break;

			case 1:
				int_count = get_int_count(iter, col_num); //
				int_count_all = get_int_count(iter, col_count); //
				switch(retype)
				{
				case 0:
					break;
				case 1:
					break;
				case 2:
					float_count = get_float_count(iter, col_num); //
					float_count_all = get_float_count(iter, col_count);  //
					(*iter).col_type[col_num] = 2; //
					while(iter_record != (*iter).table_c.end()) 
					{
						for(i=float_count_all; i>float_count; i--)  //
						{
							(*iter_record).float_x[i] = (*iter_record).float_x[i-1]; //
						}
				
						(*iter_record).float_x[float_count] = (float)(*iter_record).int_x[int_count]; //

						for(i=int_count; i<int_count_all-1; i++)
						{
							(*iter_record).int_x[i] = (*iter_record).int_x[i+1]; //
						}
						iter_record++;
					}
					break;
				case 3:
					str_count = get_str_count(iter, col_num); //
					str_count_all = get_str_count(iter, col_count);  //
					(*iter).col_type[col_num] = 3; //
					while(iter_record != (*iter).table_c.end()) 
					{
						for(i=str_count_all; i>str_count; i--)  //
						{
							(*iter_record).string_x[i] = (*iter_record).string_x[i-1]; //
						}
				
						sprintf(buf, "%d", (*iter_record).int_x[int_count] );	
						(*iter_record).string_x[str_count] = buf;

						for(i=int_count; i<int_count_all-1; i++)
						{
							(*iter_record).int_x[i] = (*iter_record).int_x[i+1]; //
						}
						iter_record++;
					}
					break;
				default:
					break;
				}
				break;

			case 2:
				float_count = get_float_count(iter, col_num); //
				float_count_all = get_float_count(iter, col_count); //
				switch(retype)
				{
				case 0:
					break;

				case 1:
					int_count = get_int_count(iter, col_num); //
					int_count_all = get_int_count(iter, col_count);  //
					(*iter).col_type[col_num] = 1; //
					while(iter_record != (*iter).table_c.end()) 
					{
						for(i=int_count_all; i>int_count; i--)  //
						{
							(*iter_record).int_x[i] = (*iter_record).int_x[i-1]; //
						}
				
						(*iter_record).int_x[int_count] = (int)(*iter_record).float_x[float_count]; //

						for(i=float_count; i<float_count_all-1; i++)
						{
							(*iter_record).float_x[i] = (*iter_record).float_x[i+1]; //
						}
						iter_record++;
					}
					break;

				case 2:
					break;

				case 3:
					str_count = get_str_count(iter, col_num); //
					str_count_all = get_str_count(iter, col_count);  //
					(*iter).col_type[col_num] = 3; //
					while(iter_record != (*iter).table_c.end()) 
					{
						for(i=str_count_all; i>str_count; i--)  //
						{
							(*iter_record).string_x[i] = (*iter_record).string_x[i-1]; //
						}
				
						sprintf(buf, "%.2f", (*iter_record).float_x[float_count] );	
						(*iter_record).string_x[str_count] = buf;

						for(i=float_count; i<float_count_all-1; i++)
						{
							(*iter_record).float_x[i] = (*iter_record).float_x[i+1]; //
						}
						iter_record++;
					}
					break;
				default:
					break;
				}
				break;
			case 3:
			//	cout << "���ܴ�text����ת�ɱ��" << endl; // for debug
				cout << "error";
				return -1;
				break;
			default:
				break;
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

// update ��������, ���� col_name ��ֵΪvalue���ҵ���Ӧ��Ҫ�޸ĵļ�¼�����������зֱ��������Ͷ�Ӧ��ֵ���ַ��������Կ�����־����
int update_table(string & table_name, string & col_name, string & value, \
	string col_update[], string value_update[], int cmp)
{
	if(isExit_table(table_name))
	{
		if(isExit_column2(table_name, col_update) && isExit_column(table_name, col_name))
		{
			int i, j;
			int count = 0;
			int num1; // ָ�������ڵ�λ��
			list<table>::iterator iter = (*iter_current_db).db_c.begin(); // ָ����ָʾ��
			list <record>::iterator iter_record; //ָ���¼

			iter = find_table(table_name);
			count = column_count(iter);

			iter_record = (*iter).table_c.begin();  // ָ���һ����¼

			//�������col_name�洢������
			for(i=0; i<count; i++)
			{
				if( 0 == _stricmp(col_name.c_str(),(*iter).properity[i].c_str()) ) // �ҵ�ָ����
				{
					num1 = i+1;
					break;
				}
			}

			for(j=0; j<(*iter).table_c.size(); j++) //������¼
			{
				if(where_cmp(iter, iter_record, col_name, value, cmp))
				{
					i = 0;
					while("" != col_update[i])
					{
						set_col_num(iter, iter_record, col_update[i], value_update[i]);
						i++;
					}
				}
		/*		switch(cmp)
				{
				case 0:
					if ( value == get_record(iter, iter_record, num1) )  // ������ֵ
					{
						// iter_record��ʱָ��ľ���Ҫ�޸ĵļ�¼��
						i=0;
						while("" != col_update[i])
						{
							set_col_num(iter, iter_record, col_update[i], value_update[i]);
							i++;
						}
					}
					break;
				case 1:
					if ( value > get_record(iter, iter_record, num1) )  // ������ֵ
					{
						// iter_record��ʱָ��ľ���Ҫ�޸ĵļ�¼��
						i=0;
						while("" != col_update[i])
						{
							set_col_num(iter, iter_record, col_update[i], value_update[i]);
							i++;
						}
					}
					break;
					case -1:
					if ( value < get_record(iter, iter_record, num1) )  // ������ֵ
					{
						// iter_record��ʱָ��ľ���Ҫ�޸ĵļ�¼��
						i=0;
						while("" != col_update[i])
						{
							set_col_num(iter, iter_record, col_update[i], value_update[i]);
							i++;
						}
					}
					break;
					case 2:
					if ( value >=  get_record(iter, iter_record, num1) )  // ������ֵ
					{
						// iter_record��ʱָ��ľ���Ҫ�޸ĵļ�¼��
						i=0;
						while("" != col_update[i])
						{
							set_col_num(iter, iter_record, col_update[i], value_update[i]);
							i++;
						}
					}
					break;
					case -2:
					if ( value <= get_record(iter, iter_record, num1) )  // ������ֵ
					{
						// iter_record��ʱָ��ľ���Ҫ�޸ĵļ�¼��
						i=0;
						while("" != col_update[i])
						{
							set_col_num(iter, iter_record, col_update[i], value_update[i]);
							i++;
						}
					}
					break;
					case 3:
					if ( value != get_record(iter, iter_record, num1) )  // ������ֵ
					{
						// iter_record��ʱָ��ľ���Ҫ�޸ĵļ�¼��
						i=0;
						while("" != col_update[i])
						{
							set_col_num(iter, iter_record, col_update[i], value_update[i]);
							i++;
						}
					}
					break;
					default:
						break;
				}
				*/
				

				iter_record++;

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

// �޸ı������һ����¼
int update_table_last(string & table_name, string col_update[], string value_update[])
{
	if(isExit_table(table_name))
	{
		if(isExit_column2(table_name, col_update))
		{
			int i;
			list<table>::iterator iter = (*iter_current_db).db_c.begin(); // ָ����ָʾ��
			list <record>::iterator iter_record; //ָ���¼

			iter = find_table(table_name);
			iter_record = --(*iter).table_c.end();  // ָ�����һ����¼

			i=0;
			while("" != col_update[i])
			{
				set_col_num(iter, iter_record, col_update[i], value_update[i]);
				i++;
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