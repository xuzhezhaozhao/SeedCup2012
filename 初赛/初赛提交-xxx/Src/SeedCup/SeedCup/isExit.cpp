#include"SeedCup.h"

//是否存在，忽略大小写
bool isExit_database(string database_name)
{
	list <db>::iterator iter_db = all_db.begin();
	while(iter_db != all_db.end())
	{
		if(0 == _stricmp(database_name.c_str(), (*iter_db).db_name.c_str()))
		{
			return true;
		}
		iter_db++;
	}

	return false;
}

bool isExit_table(string table_name)
{
	list<table>::iterator iter_table = (*iter_current_db).db_c.begin();

	while(iter_table != (*iter_current_db).db_c.end())
	{
		if(0 == _stricmp(table_name.c_str(), (*iter_table).table_name.c_str()))
		{
			return true;
		}
		iter_table++;
	}
	return false;
}

bool isExit_column(string table_name, string col_name)
{
	list<table>::iterator iter_table = find_table(table_name);
	int i = 0;
	while("" != (*iter_table).properity[i])
	{
		if(0 == _stricmp(col_name.c_str(), (*iter_table).properity[i].c_str()))
		{
			return true;
		}
		i++;
	}

	return false;
}

bool isExit_table2(string database_name, string table_name)
{
	list<db>::iterator iter_db = all_db.begin();
	while(iter_db != all_db.end())
	{
		if(0 == _stricmp((*iter_db).db_name.c_str(), database_name.c_str()))
		{
			break;
		}
		iter_db++;
	}
	list<table>::iterator iter_table = (*iter_db).db_c.begin();

	while(iter_table != (*iter_db).db_c.end())
	{
		if(0 == _stricmp(table_name.c_str(), (*iter_table).table_name.c_str()))
		{
			return true;
		}
		iter_table++;
	}
	return false;
}

bool isExit_column2(string table_name, string col_name[])
{
	int i = 0;
	while("" != col_name[i])
	{
		if(false == isExit_column(table_name, col_name[i]))
		{
			return false;
		}
		i++;
	}

	return true;
}

//是否同名，不忽略大小写
bool isSame_database(string database_name)
{
	list <db>::iterator iter_db = all_db.begin();
	while(iter_db != all_db.end())
	{
		if(database_name == (*iter_db).db_name)
		{
			return true;
		}
		iter_db++;
	}

	return false;
}

bool isSame_table(string table_name)
{
	list<table>::iterator iter_table = (*iter_current_db).db_c.begin();

	while(iter_table != (*iter_current_db).db_c.end())
	{
		if(table_name == (*iter_table).table_name)
		{
			return true;
		}
		iter_table++;
	}
	return false;
}