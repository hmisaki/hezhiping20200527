//行人的定义
#pragma once
#include <vector>

class Path;
class People;

struct Task
{
	int task_id;				//本任务是第几个任务
	int start_time;				//任务起始时间
	int end_time;				//任务结束时间
	int job_time;				//任务花费时间
	char path_name[128];		//路径名，对tunnel的任务需要特殊处理
};
class People
{
	friend class City;

public:
	People(const char* people_name,int ready_time);
	~People(void);
	void put_a_task(Task task);			//置入一个任务，且会根据job_id进行排序

	std::vector<Task> m_tasks;			//行人所有需要进行的的任务
	private:
	char m_name[128];					//名字
	int m_ready_time;					//行人准备时间
};

