#pragma once
class City
{
public:
	City(void);
	~City(void);
	void cal_people_time(vector<People*> people);
	int curr_tunnel_time;
};

