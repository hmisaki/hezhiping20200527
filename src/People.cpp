#include "People.h"
#include <algorithm>


static bool task_compare(Task task1,Task task2)
{
	return task1.task_id >task2.task_id ? false:true;
}

People::People(const char* people_name,int ready_time)
{
	strcpy(m_name,people_name);
	m_ready_time = ready_time;
}


People::~People(void)
{
}

void People::put_a_task(Task task){
	m_tasks.push_back(task);							//压入一个任务
	std::sort(m_tasks.begin(),m_tasks.end(),task_compare);//对所有任务依照task_id进行排序
	
}