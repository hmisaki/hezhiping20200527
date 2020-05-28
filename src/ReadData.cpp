#include "ReadData.h"

string get_string_field(SACommand &cmd, string field)
{
	SAString sastr = cmd.Field(field.c_str()).asString();
	string s = sastr.GetBuffer(STRING_SIZE);
	return s;
}
ReadData::ReadData(void)
{
}


ReadData::~ReadData(void)
{
}


void ReadData::readpeople()
{
	
	m_cmd.setCommandText("select *  from t_people");
	m_cmd.Execute();
	while(m_cmd.FetchNext())
	{
		string name = get_string_field(m_cmd, "stock_name");

	}

}
void ReadData::readtasks()
{
	m_conn.Connect(m_filename, "", "", SA_SQLite_Client);
	m_cmd.setConnection(&m_conn);
	m_cmd.setCommandText("select *  from t_job");
	m_cmd.Execute();
	while(m_cmd.FetchNext())
	{

	}
}
void ReadData::connect_db()
{
	printf("m_filename %s\n", m_filename);
	m_conn.Connect(m_filename, "", "", SA_SQLite_Client);
	m_cmd.setConnection(&m_conn);
}

void ReadData::disconnect_db()
{
	m_conn.Disconnect();
}
