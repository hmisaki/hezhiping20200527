#pragma once
#include <vector>
class People;

class City
{
public:
	City(int tunnel_ready_time);
	City();
	~City(void);
	void cal_people_time(std::vector<People*> peoples); //���㰴�ձ�˳���ͨ�����ʱÿ���˵������ʱ��

private:
	int m_tunnel_ready_time;			//�����ʼ����ʱ��
};

