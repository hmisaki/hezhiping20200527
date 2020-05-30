//���˵Ķ���
#pragma once
#include <vector>

class Path;
class People;

struct Task
{
	int task_id;				//�������ǵڼ�������
	int start_time;				//������ʼʱ��
	int end_time;				//�������ʱ��
	int job_time;				//���񻨷�ʱ��
	char path_name[128];		//·��������tunnel��������Ҫ���⴦��
};
class People
{
	friend class City;

public:
	People(const char* people_name,int ready_time);
	~People(void);
	void put_a_task(Task task);			//����һ�������һ����job_id��������

	std::vector<Task> m_tasks;			//����������Ҫ���еĵ�����
	private:
	char m_name[128];					//����
	int m_ready_time;					//����׼��ʱ��
};

