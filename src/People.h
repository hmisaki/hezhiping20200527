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
	int task_type;
};
class People
{
public:
	People(void);
	~People(void);
	vector<Task> task;			//行人所有需要的任务
	char name[128];				//名字
};

