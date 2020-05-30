#pragma once
#include "sqlapi/SQLAPI.h"
#include <string>
#include <vector>
#include <map>
#include "People.h"
#include "City.h"
#define  STRING_SIZE 128
using namespace std;
class ReadData
{
public:
	ReadData(const char *sql_path);
	~ReadData(void);
	void readpeople(std::vector<People*> &people);		//��ȡ��������
	void readtasks();		//��ȡ��������·������
	void connect_db();		//�������ݿ�
	void disconnect_db();	//�Ͽ����ݿ�
	void freepeoplememory(std::vector<People*> &people);	//�ͷ�readpeople�з�����ڴ�
private:
	SAConnection m_conn;	//���ݿ���
	SACommand m_cmd;
	char sql_file_path[128];	//sql��·��
	std::map<string,People*> map_people_2_obj;	//ӳ�������Ͷ�����֮���ȡtaskʱֱ�Ӳ���people������������
};

