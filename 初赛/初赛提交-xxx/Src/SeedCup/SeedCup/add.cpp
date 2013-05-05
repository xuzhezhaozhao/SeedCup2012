#include"SeedCup.h"

//��Ӽ�¼, ����¼Ϊ��ʱ��int��float����Ϊ��65535��string��Ϊ "#"
int add_record(string & table_name, string col_record[])
{
	if(isExit_table(table_name))
	{
		int i;
		int count = 0; // ��¼�������Եĸ���

		int col_int; 
		float col_float;
		string col_str;

		int int_count = 0;
		int float_count = 0;
		int str_count = 0;
		struct record new_record = { 
			{0}, 
			{0},
			{""}
		};
	
		list<table>::iterator iter = find_table(table_name); // ָ����ָʾ��

		count = column_count(iter);

		for(i=0; i<count; i++)
		{
			if("" == col_record[i])
			{

			}
			switch( (*iter).col_type[i] )
			{
			case 0:
				break;

			case 1:
				if("" == col_record[i])
				{
					new_record.int_x[int_count] = -65535;
					int_count++;
				}
				else
				{
					col_int = atoi(col_record[i].c_str() );
					new_record.int_x[int_count] = col_int;
					int_count++;
				}
				break;
			case 2:
				if("" == col_record[i])
				{
					new_record.float_x[float_count] = -65535;
					float_count++;
				}
				else
				{
					col_float = atof(col_record[i].c_str()); 
					new_record.float_x[float_count] = col_float;
					float_count++;
				}
				break;

			case 3:
				if("" == col_record[i])
				{
					new_record.string_x[str_count] = "";
					str_count++;
				}
				else
				{
					col_str = col_record[i];
					new_record.string_x[str_count] = col_str;
					str_count++;
				}
				break;

			default:
				break;
			}
		}
			
		(*iter).table_c.push_back(new_record);  //���µļ�¼��ӵ�����
		return 1;	
	}
	else
	{
		cout << "error" << endl;
		return -1;
	}
}

//��ָ������Ӽ�¼���������Կս���
int add_record2(string & table_name,string col_name[], string col_record[])
{
	if(isExit_table(table_name))
	{
		if(isExit_column2(table_name, col_name))
		{
			struct record new_record = { 
				{-65535}, 
				{-65535},
				{"#"}
			};
	
			list<table>::iterator iter = find_table(table_name); // ָ����ָʾ��
			(*iter).table_c.push_back(new_record);  //���µļ�¼��ӵ�����
			update_table_last(table_name, col_name, col_record);
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


