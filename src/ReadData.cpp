#include "ReadData.h"

string get_string_field(SACommand &cmd, string field)
{
	SAString sastr = cmd.Field(field.c_str()).asString();
	string s = sastr.GetBuffer(STRING_SIZE);
	return s;
}
ReadData::ReadData(const char *sql_path)
{
	strcpy(this->sql_file_path,sql_path);
}


ReadData::~ReadData(void)
{

}


void ReadData::readpeople(std::vector<People*> &people)
{
	string people_name;
	try{
		m_cmd.setCommandText("select *  from t_people");
		m_cmd.Execute();
		People *temp_people;
		while(m_cmd.FetchNext())//获取所有记录的人名，生成对象
		{
			people_name = get_string_field(m_cmd, "name");
			temp_people = new People(people_name.c_str(),0);
			map_people_2_obj[people_name] = temp_people;
			people.push_back(temp_people);
		}
	}catch(SAException &x)//捕获数据库错误
	{
		printf("read t_people table wrong: %s\n", (const char*)x.ErrText());
		throw -1;
	}

}

void  ReadData::freepeoplememory(std::vector<People*> &people)
{
	for (int people_index=0;people_index<people.size();people_index++)
	{
		delete people[people_index];
	}
	people.clear();
}

void ReadData::readtasks()
{
	string people_name;
	string path_name;
	People *people= NULL;
	try{
		m_cmd.setCommandText("select *  from t_job group by people, seq");
		m_cmd.Execute();
		while(m_cmd.FetchNext())//获取所有的task 并压入对应人的task列表中
		{
			people_name =  get_string_field(m_cmd, "people");
			people = map_people_2_obj[people_name];
			Task task;
			task.task_id =  m_cmd.Field("seq").asLong();
			task.job_time =  m_cmd.Field("pass_time").asLong();
			path_name = get_string_field(m_cmd, "path_name");
			strcpy(task.path_name,path_name.c_str());
			people->put_a_task(task);
		}

	}catch(SAException &x)//捕获数据库错误
	{
		printf("read t_job table wrong: %s\n", (const char*)x.ErrText());
	}
}
void ReadData::connect_db()
{
	m_conn.Connect(sql_file_path, "", "", SA_SQLite_Client);
	m_cmd.setConnection(&m_conn);
}

void ReadData::disconnect_db()
{
	m_conn.Disconnect();
}
