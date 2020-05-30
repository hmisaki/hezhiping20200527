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
	int curr_tunnel_time =m_tunnel_ready_time;				//����ʱ��ʱ��ȡ�����ʼ����ʱ��

	for (int people_index =0;people_index<peoples.size();people_index++)	//����ģ�ͼ򻯣�ֻ��һ�����������ֻҪȷ���˹������˳��
																			//���㵽ĳ����ʱ��ǰ�������˵�ʱ��һ���Ѿ��������
	{
		People *people = peoples[people_index];
		for (int task_index =0;task_index< people->m_tasks.size();task_index++)//��ÿ���˵������������μ���ʱ�䣬��һ������ʼʱ������ǰһ���Ľ���ʱ��
		{
			Task *task=  &people->m_tasks[task_index];
			int people_ready_time =0;

			if(task_index ==0){												//����ǵ�һ��������ô��������׼����ʱ����ǳ���ʱ��
				people_ready_time = people->m_ready_time;
			}else{
				people_ready_time = people->m_tasks[task_index-1].end_time;//����ǵ�֮��������׼��ʱ����ǰһ������Ľ���ʱ��
			}

			if(strcmp(task->path_name,"tunnel") ==0)					//�����������tunnel ,Ҳ�����������ô��Ҫ�������ʲôʱ��׼����
			{
				task->start_time = my_max(people_ready_time,curr_tunnel_time);	//��ȡ�˺����׼��ʱ��Ĵ�����Ϊ����ʼʱ��
				task->end_time = task->start_time+task->job_time;				//��������ʼ���������ʱ������������ʱ��
				curr_tunnel_time = task->end_time;								//��ʱ�������׼��ʱ������һ���˽���ʹ��
			}else{																//������Ҫ�������׼��ʱ��
				task->start_time = people_ready_time;							//ֱ�ӻ�ȡ�˵�׼��ʱ��
				task->end_time = task->start_time+task->job_time;				//��������ʼ���������ʱ������������ʱ��
			}
		}
	}
}