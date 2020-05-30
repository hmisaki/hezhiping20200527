#include "City.h"
#include "People.h"
#define my_max(a,b)            (((a) > (b)) ? (a) : (b))

City::City(int tunnel_ready_time)
{
	m_tunnel_ready_time = tunnel_ready_time;
}

City::City():m_tunnel_ready_time(0){

}

City::~City(void)
{
}

void City::cal_people_time(std::vector<People*> peoples)
{
	int curr_tunnel_time =m_tunnel_ready_time;				//计算时间时获取隧道初始可用时间

	for (int people_index =0;people_index<peoples.size();people_index++)	//由于模型简化，只有一个隧道，所以只要确定了过隧道的顺序，
																			//计算到某个人时，前面所有人的时间一定已经计算完毕
	{
		People *people = peoples[people_index];
		for (int task_index =0;task_index< people->m_tasks.size();task_index++)//对每个人的所有任务依次计算时间，后一个任务开始时间依赖前一个的结束时间
		{
			Task *task=  &people->m_tasks[task_index];
			int people_ready_time =0;

			if(task_index ==0){												//如果是第一个任务，那么这个任务的准备好时间就是出门时间
				people_ready_time = people->m_ready_time;
			}else{
				people_ready_time = people->m_tasks[task_index-1].end_time;//如果是第之后的任务的准备时间是前一个任务的结束时间
			}

			if(strcmp(task->path_name,"tunnel") ==0)					//如果任务名是tunnel ,也就是隧道，那么需要考虑隧道什么时间准备好
			{
				task->start_time = my_max(people_ready_time,curr_tunnel_time);	//获取人和隧道准备时间的大着作为任务开始时间
				task->end_time = task->start_time+task->job_time;				//根据任务开始和任务持续时间计算任务结束时间
				curr_tunnel_time = task->end_time;								//及时更新隧道准备时间让下一个人进行使用
			}else{																//否则不需要考虑隧道准备时间
				task->start_time = people_ready_time;							//直接获取人的准备时间
				task->end_time = task->start_time+task->job_time;				//根据任务开始和任务持续时间计算任务结束时间
			}
		}
	}
}