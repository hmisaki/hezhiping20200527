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
	void readpeople(std::vector<People*> &people);		//读取行人数据
	void readtasks();		//读取行人所有路线数据
	void connect_db();		//链接数据库
	void disconnect_db();	//断开数据库
	void freepeoplememory(std::vector<People*> &people);	//释放readpeople中分配的内存
private:
	SAConnection m_conn;	//数据库句柄
	SACommand m_cmd;
	char sql_file_path[128];	//sql的路径
	std::map<string,People*> map_people_2_obj;	//映射人名和对象，在之后读取task时直接操作people对象填入数据
};

