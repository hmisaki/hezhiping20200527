#include<iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "People.h"
#include "ReadData.h"
#include "sqlapi/SQLAPI.h"
#include "People.h"
using namespace std;


int cal_spend_time(vector<People*> &peoples)
{
	int spend_time =0;
	for (int people_index=0;people_index<peoples.size();people_index++)	//直接根据每个人的最后一个任务结束时间和第一个人任务的起始时间算出每个人花费的时间
	{
		int task_num =(int)peoples[people_index]->m_tasks.size();
		spend_time+= peoples[people_index]->m_tasks[task_num-1].end_time 
			- peoples[people_index]->m_tasks[0].start_time;
	}

	return spend_time;
}

void get_best_plan(vector<People*> src_plan,City &city,vector<People*> &best_result,int shortest_time)
{
	int people_num = (int)src_plan.size();	//获取人数
	int plan_spend_time =0;
	int *seq_array = new int[people_num];	//为生成全排列做辅助准备
	for(int seq_index=0;seq_index< people_num;seq_index++ ){
		seq_array[seq_index] = seq_index;   //生成0，1，2，3，4，5...这样的数组
	}
	do{
		vector<People *> temp_plan;
		for (int seq_index =0;seq_index<people_num;seq_index++)
		{
			temp_plan.push_back(src_plan[seq_array[seq_index]]); //根据数组映射成新的方案
		}

		city.cal_people_time(temp_plan);						//计算这个方案的时间
		plan_spend_time =cal_spend_time(temp_plan);				//计算消耗的时间

		if(plan_spend_time<shortest_time)						//如果这个方案比最好的还要好就记录，并更新最小时间
		{
			best_result= temp_plan;
			shortest_time = plan_spend_time;
		}
      }while(next_permutation(seq_array,seq_array+people_num));//对上面的数组生成全排列

	delete[] seq_array;											//释放辅助数据结构
}

int main()
{
	vector<People*> peoples;
	vector<People*> best_result;
	City city;
	int shortest_time =0;

	ReadData read_db_data("../../Data/inputdata.db");
	read_db_data.connect_db();					//链接数据库读取所有数据，形成数据结构
	read_db_data.readpeople(peoples);
	read_db_data.readtasks();
	read_db_data.disconnect_db();				//断开数据库释放资源

	city.cal_people_time(peoples);				//计算初始解任务的时间
	shortest_time = cal_spend_time(peoples);	//根据任务情况计算时间

	best_result = peoples;						//记录到结果集中，默认初始解是最好的解
	cout<<"src_time="<<shortest_time<<endl;;	

	get_best_plan(peoples,city,best_result,shortest_time);//尝试优化初始解

	city.cal_people_time(best_result);						//重新计算最好解的时间
	shortest_time = cal_spend_time(best_result);			//输出优化后的最短时间
	cout<<"best_time ="<<shortest_time<<endl;

	read_db_data.freepeoplememory(peoples);

	return 0;
} 