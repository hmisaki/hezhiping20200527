#pragma once
#define  STRING_SIZE 128

class ReadData
{
public:
	ReadData(void);
	~ReadData(void);
	void readpeople();		//读取行人数据
	void readtasks();		//读取行人所有路线数据
	void connect_db();		//链接数据库
	void disconnect_db();	//断开数据库
private:
	SAConnection m_conn;	//数据库句柄
	SACommand m_cmd;		
};

