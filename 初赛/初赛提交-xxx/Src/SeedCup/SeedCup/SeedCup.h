#ifndef _SEEDCUP_H_
#define _SEEDCUP_H_

#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include <stack>

using namespace std;

/***�������ݽṹ****/
struct record{
	int int_x[20];
	float float_x[20];
	string string_x[20];
};
struct table{
	list <record> table_c;
	string table_name;
	string properity[50];  //��������
	int col_type[50];   //������Ե��������ͣ�0��NONE 1��int  2��float  3��string(��TEXT)
};
struct db{
	list <table> db_c;
	string db_name;
};

//ȫ�ֱ���
extern list <db>::iterator iter_current_db; // ָʾ����ʹ�ã�USE�������ݿ�
extern list <db> all_db;
extern int gram;
extern bool isUse;
extern bool divider;  // ��������0ʱΪtrue


/**************************************************************/
/*��������*/
int covert_sentence(string & str, string cut[]);
bool iskeyword(string test_word);
int is_exit_db(string & database_name);
void sort_string_incr(string str[], int len);
void sort_string_desc(string str[], int len);


int create_database(string & database_name);
int truncate_database(string & database_name);
int truncate_table(string & table_name);
int drop_database(string & datebse_name);

void show_database(int order_type);
int use_database(string & database_name);

int create_table(string & table_name);
int drop_table(string & database_name, string & table_name);
int show_table(string & database_name, int order_type);

list<table>::iterator find_table(string & table_name);

int create_column(string & table_name, string & column_name, int type);
int delete_column(string & table_name, string & column_name);

int rename_database(string & old_db_name, string & new_db_name);
int rename_table(string & old_tb_name, string & new_tb_name);
int retype_column(string & table_name, string & column_name, int retype);

int show_column(string & database_name, string & table_name, int order_type);

int add_record(string & table_name, string col_record[]);
int add_record2(string & table_name,string col_name[], string col_record[]);
void delete_record(string & table_name, string & col_name, string & value, int cmp);

string get_record(list<table>::iterator iter, list<record>::iterator iter_record, int num);
int get_col_type(string & table_name, string & col_name);
int get_col_num(list<table>::iterator iter, string & col_name);
int get_int_count(list<table>::iterator iter, int num);
int get_float_count(list<table>::iterator iter, int num);
int get_str_count(list<table>::iterator iter, int num);

int set_col_num(list<table>::iterator iter, list<record>::iterator iter_record, string & col_name, string & value);
string add_quote(string str);

int generate_select( string & table_name, string col_name[], int *select);
int display_select_column(string & table_name, string col_name[]);
string display_select_record( string & table_name, string col_name[], list<record>::iterator iter_record);

int column_count(list<table>::iterator iter);
int update_table(string & table_name, string & col_name, string & value, \
	string col_update[], string value_update[], int cmp);
int update_table_last(string & table_name, string col_update[], string value_update[]);
void swap_record(list<record>::iterator iter1, list<record>::iterator iter2);

int sort_table_incr(string & table_name, string by_col_name);
int sort_table_desc(string & table_name, string by_col_name);
int sort_table_default(string & table_name, string by_col_name);

int select_where_cmp(string & table_name, string select_col_name[], string & cmp_col_name, string & cmp_value, int cmp, string & by_col_name, int order_by);
int select_where_between(string & table_name, string select_col_name[], string & bet_col_name, string & bet_value1, string & bet_value2, string & by_col_name, int order_by);

bool strMatch(char *pat,char *str);
int select_where_like(string & table_name, string select_col_name[], string & like_col_name, string & like_value, string & by_col_name, int order_by);

bool where_cmp(list<table>::iterator iter, list <record>::iterator iter_record,  string  & col_name, string value, int cmp);
bool where_between(list<table>::iterator iter, list <record>::iterator iter_record,string & col_name, string value1, string value2);
bool where_like(list<table>::iterator iter, list <record>::iterator iter_record, string & like_col_name, string & like_value);

int select_where_and(string & table_name, string select_col_name[], string & cmp_col_name1, string & cmp_value1, int cmp1, \
	string & cmp_col_name2, string & cmp_value2, int cmp2, string & by_col_name, int order_by);

int select_where_or(string & table_name, string select_col_name[], string & cmp_col_name1, string & cmp_value1, int cmp1, \
	string & cmp_col_name2, string & cmp_value2, int cmp2, string & by_col_name, int order_by);

void format_sentence(string & sentence);

void save_blank(string & sentence);

void null_to(string & sentence);

void add_blank(string & sentence);
void add_blank2(string & sentence);

void to_blank(string & sentence);

void encode_str(string & cut);

void get_gram(string single[], int len);

bool is_contain(string str,string contain[], int len);
void sol_bug(string & sentence);

int delete_enter(string &str);// \n ��ɿո�
int delete_yinhao(string &str);//ȥ������������ӿո�
int delete_zhongkuohao(string &str);//ȥ�������Ų�����ӿո�
int where_add_kongge(string &str);//��>,<,==,<=,>=,~=,������ӿո�
int yinhao_add_jinhao(string &str);//��Ҫ��ɾ��������ǰִ�С����#	


int exe_commands(string single[], int len);
void execute(string line);

float calc(float a, char opr, float b);
int GetLevel(char opr);
float yunsuan(string &str_in);

int execute_file(string inputfile);
int math_to(string &str);

int get_single(string & str, string single[]);

bool isempty_table(string table_name);

bool isExit_database(string database_name);

bool isExit_table(string table_name);
bool isExit_table2(string database_name, string table_name);

bool isExit_column(string table_name, string col_name);
bool isExit_column2(string table_name, string col_name[]);

void add_blank3(string & sentence);

bool check_gram(string single[], int len);
int delete_blank(string &str);

bool isSame_database(string database_name);
bool isSame_table(string table_name);


#endif