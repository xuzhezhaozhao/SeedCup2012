/* ʵ��5.2���ܣ�ָ���� */


#ifndef _5_2_H_
#define _5_2_H_

using namespace std;

//���ܣ������к������й�ռ��
void assignNull();

//���ܣ�������beginλ�ú�ĵ�һ���������й�ռ��
//����ֵ�����غ�����β����һ���кż�1��ֵ����1��ʾû���ҵ�������
int funcAssignNull(int begin);

//���ܣ�����ں���func��pos�� λ�ó��ֵ�free(check_p),��ô�ڸú����������ڴ�pos+1�п�ʼ����Ƿ���check_p = NULL����
//������func[] ���溯���е����飬 flen ���������鳤�ȣ� pos ����free��λ�ã���Ժ������飩��check_p free��ָ��
//����ֵ��true ��ʾ�й�ղ���
bool checkNull(string func[], int flen, int pos, string check_p);


#endif