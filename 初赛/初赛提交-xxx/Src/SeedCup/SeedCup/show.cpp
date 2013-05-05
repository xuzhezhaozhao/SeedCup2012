#include"SeedCup.h"

//��ӡ���ݿ���,order_typeΪ�������ݣ���1��������˳��		0������		1������
void show_database(int order_type)
{
	string str[50] = {""};
	int len = 0;
	int i=0;
	list<db>::iterator iter = all_db.begin();
	while(iter != all_db.end())
	{
		str[i] = (*iter).db_name;
		i++;
		iter++;
	}
	len = i;
	if("" == str[0])
	{
		cout << "$" << endl;
	}
	else
	{
		switch(order_type)
		{
		case -1: //��������˳���ӡ
			for(i=0; i<len-1; i++)
			{
				cout << str[i] << ",";
			}
			cout << str[i] << endl;
			break;
		case 0: //����
			sort_string_incr(str, len);
			break;
		case 1: //����
			sort_string_desc(str, len);
			break;
		}
	}
}

//��ӡ��ǰ���ݿ��б���
int show_table(string & database_name, int order_type)
{
	if(isExit_database(database_name))
	{
		string str[50] = {""};
		int len = 0;
		int i=0;	
		list<db>::iterator iter2 = all_db.begin();
		list<table>::iterator iter;

		for(i=0; i<all_db.size(); i++)
		{
			if(0 == _stricmp( database_name.c_str(), (*iter2).db_name.c_str() ) ) //�ҵ�ָ����
			{
				break;
			}
			iter2++;
		}

		iter = (*iter2).db_c.begin(); 
		i = 0;
		while(iter != (*iter2).db_c.end())
		{
			str[i] = (*iter).table_name;
			i++;
			iter++;
		}
		len = i;
		if(str[0] == "")
		{
			cout << "$" << endl;
			return -1;
		}
		else
		{
			switch(order_type)
			{
			case -1: //��������˳���ӡ
				for(i=0; i<len-1; i++)
				{
					cout << str[i] << ",";
				}
				cout << str[i] << endl;
				break;
			case 0: //����
				sort_string_incr(str, len);
				break;
			case 1: //����
				sort_string_desc(str, len);
				break;
			}
			return 0;
		}
		
	}
	else
	{		
		cout << "error" <<endl;
		return -1;
	}
}

// ��ӡָ�����ȫ������
int show_column(string & database_name, string & table_name, int order_type)
{
	if(isExit_database(database_name))
	{

		int i, j;
		int len;
		int count = 0; //����
		int flag1 = 0;
		int flag2 = 0;
		string str[50];
		list<table>::iterator iter;
		list<db>::iterator iter_db = all_db.begin();

		while(iter_db != all_db.end())
		{
			if((*iter_db).db_name == database_name)
			{
				iter = (*iter_db).db_c.begin();
				while((iter != (*iter_db).db_c.end()))
				{
					if(0 == _stricmp(table_name.c_str(), (*iter).table_name.c_str() ))
					{
						for(j=0; j<50; j++)
						{
							if( (*iter).properity[j] != "" )
							{
								count++;
							}
							else
								break;
						}

						for(j=0; j<count; j++)
						{
								str[j] = (*iter).properity[j];
						}
						len = count;
						if(str[0] == "")
						{
							cout << "$" << endl;
						}
						else
						{
							switch(order_type)
							{
							case -1: //��������˳���ӡ
								for(i=0; i<len-1; i++)
								{
									cout << str[i] << ",";
								}
								cout << str[i] << endl;
								break;
							case 0: //����
								sort_string_incr(str, len);
								break;
							case 1: //����
								sort_string_desc(str, len);
								break;
							}
						}
						flag2 = 1;
					}

					iter++;
				}
				flag1 = 1;
			}			
		
			iter_db++;
		}
		if(0 == flag1 || 0 == flag2)
		{
			cout << "$" << endl;
			return -1;
		}

		return 0;
	}
	else
	{
		cout << "error" << endl;
		return -1;
	}
}

