#ifndef _SEEDCUP2_H_
#define _SEEDCUP2_H_

// ��׼ͷ�ļ�
#include<iostream>
#include<fstream>
#include<string>

//�Զ���ͷ�ļ�
#include"initial.h"
#include"strParse.h"
#include"pickup.h"
#include"auxiliary.h"
#include"display.h"
#include"5_1.h"
#include"5_2.h"
#include"5_3_1.h"
#include"5_3_2.h"
#include"5_3_3.h"
#include"5_3_4.h"
#include"5_4.h"
#include"5_5_1.h"
#include"5_5_2.h"
#include"5_5_3.h"
#include"5_5_4.h"
#include"5_6.h"
#include"5_7_1_Custom.h"
#include"5_7_2_Custom.h"

using namespace std;

//ȫ�ֱ���
extern string command[1000];  // �������������ڸ�������
extern int cmdCount;     // ��¼�������������
extern int errNum[255];
extern int errType[255];
extern int errLen; 

#endif