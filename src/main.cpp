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
	for (int people_index=0;people_index<peoples.size();people_index++)	//ֱ�Ӹ���ÿ���˵����һ���������ʱ��͵�һ�����������ʼʱ�����ÿ���˻��ѵ�ʱ��
	{
		int task_num =(int)peoples[people_index]->m_tasks.size();
		spend_time+= peoples[people_index]->m_tasks[task_num-1].end_time 
			- peoples[people_index]->m_tasks[0].start_time;
	}

	return spend_time;
}

void get_best_plan(vector<People*> src_plan,City &city,vector<People*> &best_result,int shortest_time)
{
	int people_num = (int)src_plan.size();	//��ȡ����
	int plan_spend_time =0;
	int *seq_array = new int[people_num];	//Ϊ����ȫ����������׼��
	for(int seq_index=0;seq_index< people_num;seq_index++ ){
		seq_array[seq_index] = seq_index;   //����0��1��2��3��4��5...����������
	}
	do{
		vector<People *> temp_plan;
		for (int seq_index =0;seq_index<people_num;seq_index++)
		{
			temp_plan.push_back(src_plan[seq_array[seq_index]]); //��������ӳ����µķ���
		}

		city.cal_people_time(temp_plan);						//�������������ʱ��
		plan_spend_time =cal_spend_time(temp_plan);				//�������ĵ�ʱ��

		if(plan_spend_time<shortest_time)						//��������������õĻ�Ҫ�þͼ�¼����������Сʱ��
		{
			best_result= temp_plan;
			shortest_time = plan_spend_time;
		}
      }while(next_permutation(seq_array,seq_array+people_num));//���������������ȫ����

	delete[] seq_array;											//�ͷŸ������ݽṹ
}

int main()
{
	vector<People*> peoples;
	vector<People*> best_result;
	City city;
	int shortest_time =0;

	ReadData read_db_data("../../Data/inputdata.db");
	read_db_data.connect_db();					//�������ݿ��ȡ�������ݣ��γ����ݽṹ
	read_db_data.readpeople(peoples);
	read_db_data.readtasks();
	read_db_data.disconnect_db();				//�Ͽ����ݿ��ͷ���Դ

	city.cal_people_time(peoples);				//�����ʼ�������ʱ��
	shortest_time = cal_spend_time(peoples);	//���������������ʱ��

	best_result = peoples;						//��¼��������У�Ĭ�ϳ�ʼ������õĽ�
	cout<<"src_time="<<shortest_time<<endl;;	

	get_best_plan(peoples,city,best_result,shortest_time);//�����Ż���ʼ��

	city.cal_people_time(best_result);						//���¼�����ý��ʱ��
	shortest_time = cal_spend_time(best_result);			//����Ż�������ʱ��
	cout<<"best_time ="<<shortest_time<<endl;

	read_db_data.freepeoplememory(peoples);

	return 0;
} 