#include"SeedCup.h"

//ʹ��ָ�����ݿ⣬���������ִ�Сд��ָ���Ŀ�����򷵻�1���������򷵻�0
int use_database(string & database_name)
{
	if(isExit_database(database_name))
	{
		int i;
		list<db>::iterator iter;
		iter = all_db.begin();
		int size = all_db.size();
		for(i=0; i<size; i++)
		{
			if(0 == _stricmp( database_name.c_str(), (*iter).db_name.c_str() ) )
			{
				break;
			}
			else
			{
				iter++;
			}	
		}
		iter_current_db = iter; 

		return 0;
	}
	else
	{
		cout << "error" << endl;
		return -1;
	}					
}