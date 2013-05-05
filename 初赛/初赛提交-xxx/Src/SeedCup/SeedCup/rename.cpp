#include"SeedCup.h"

//重命名数据库,成功1，失败0
int rename_database(string & old_db_name, string & new_db_name)
{
	if(isExit_database(old_db_name))
	{
		int i, j;
		int flag = 1;
		list<db>::iterator iter = all_db.begin();
		list<db>::iterator iter2 = all_db.begin();	
		iter = all_db.begin();
		for(i=0; i<all_db.size(); i++)
		{
			if(0 == _stricmp( old_db_name.c_str(), (*iter).db_name.c_str() ) )  //找到指定的数据库
			{
				for(j=0; j<all_db.size(); j++)
				{
					if(iter != iter2 && 0 == _stricmp( new_db_name.c_str(), (*iter2).db_name.c_str()) || new_db_name == (*iter).db_name || iskeyword(new_db_name))
					{
						flag = -1;
					}
					iter2++;
				}
				if(1 == flag)
				{
					(*iter).db_name = new_db_name;
					return 1;
				}
				else
				{
					cout << "error" << endl;
				}
			}
			iter++;
		}
	}
	else
	{
		cout << "error" <<endl;
		return -1;
	}
}

//重命名表，成功1，失败0
int rename_table(string & old_tb_name, string & new_tb_name)
{
	if(isExit_table(old_tb_name))
	{
		int j;
		int flag = 1;
		list<table>::iterator iter = find_table(old_tb_name);
		list<table>::iterator iter2 = (*iter_current_db).db_c.begin();
		
		while(iter2 != (*iter_current_db).db_c.end())
		{
			if(iter != iter2 && 0 == _stricmp(new_tb_name.c_str(), (*iter2).table_name.c_str()) || iskeyword(new_tb_name))
			{
				flag = -1;
			}
			iter2++;
		}
		if(1 == flag)
		{
			(*iter).table_name = new_tb_name;
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