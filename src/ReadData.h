#pragma once
#define  STRING_SIZE 128

class ReadData
{
public:
	ReadData(void);
	~ReadData(void);
	void readpeople();		//��ȡ��������
	void readtasks();		//��ȡ��������·������
	void connect_db();		//�������ݿ�
	void disconnect_db();	//�Ͽ����ݿ�
private:
	SAConnection m_conn;	//���ݿ���
	SACommand m_cmd;		
};

