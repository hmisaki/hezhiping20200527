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
	int task_type;
};
class People
{
public:
	People(void);
	~People(void);
	vector<Task> task;			//����������Ҫ������
	char name[128];				//����
};

