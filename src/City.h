#pragma once
#include <vector>
class People;

class City
{
public:
	City(int tunnel_ready_time);
	City();
	~City(void);
	void cal_people_time(std::vector<People*> peoples); //计算按照本顺序的通过隧道时每个人的任务的时间

private:
	int m_tunnel_ready_time;			//隧道初始可用时间
};

