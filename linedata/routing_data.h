#include <vector>
#include "defination.h"
#include <math.h> 
using namespace std;

class RoutingData{
public:
	int generate_time;
	int receive_time;
	int src;
	int dest;

	int crossing_num;
	int active_num;
	int passive_num;

	double active_loss;
	double passive_loss;
	double crossing_loss;

	vector<int> routinglist;
	RoutingData();
	RoutingData(int g_t, int r_t, int s, int d, vector<int> r_l);
	double getloss();
	int get_input_direction(int src, int dst);
	int get_output_direaction(int src, int dst);
};

RoutingData::RoutingData(){
	generate_time = 0;
	receive_time = 0;
	src = 0;
	dest = 0;
	active_loss = 0;
	passive_loss = 0;
	crossing_loss = 0;

	crossing_num = 0;
	active_num = 0;
	passive_num = 0;
}
RoutingData::RoutingData(int g_t, int r_t, int s, int d, vector<int> r_l){
	generate_time = g_t;
	receive_time = r_t;
	src = s;
	dest = d;
	routinglist = r_l;
	active_loss = 0;
	passive_loss = 0;
	crossing_loss = 0;

	crossing_num = 0;
	active_num = 0;
	passive_num = 0;
}

double RoutingData::getloss(){
	double temp = 0;
	int in_d =0;
	int out_d = get_output_direaction(routinglist[0], routinglist[1]);
	temp +=(active_number[0][out_d]*L_SW_active(chip_temp[routinglist[0]], chip_temp[routinglist[0]]) + \
			passive_number[0][out_d]*L_SW_parking(chip_temp[routinglist[0]], chip_temp[routinglist[0]]) +\
			crossing_number[0][out_d]*L_crossing);

	crossing_loss += crossing_number[in_d][out_d] * L_crossing;
	crossing_num += crossing_number[in_d][out_d];

	active_loss += active_number[in_d][out_d] * L_SW_active(chip_temp[routinglist[0]], chip_temp[routinglist[0]]);
	active_num += active_number[in_d][out_d];

	passive_loss += passive_number[in_d][out_d] * L_SW_parking(chip_temp[routinglist[0]], chip_temp[routinglist[0]]);
	passive_num += passive_number[in_d][out_d];


	for (int i = 1; i < (routinglist.size() - 1); i++)
	{
		in_d = get_input_direction(routinglist[i - 1], routinglist[i]);
		out_d = get_output_direaction(routinglist[i], routinglist[i + 1]);

		temp += (active_number[in_d][out_d] * L_SW_active(chip_temp[routinglist[0]], chip_temp[routinglist[i]]) + \
			passive_number[in_d][out_d] * L_SW_parking(chip_temp[routinglist[0]], chip_temp[routinglist[i]]) + \
			crossing_number[in_d][out_d] * L_crossing);

		crossing_loss += crossing_number[in_d][out_d] * L_crossing;
		crossing_num += crossing_number[in_d][out_d];

		active_loss += active_number[in_d][out_d] * L_SW_active(chip_temp[routinglist[0]], chip_temp[routinglist[0]]);
		active_num += active_number[in_d][out_d];

		passive_loss += passive_number[in_d][out_d] * L_SW_parking(chip_temp[routinglist[0]], chip_temp[routinglist[0]]);
		passive_num += passive_number[in_d][out_d];
	}

	in_d = get_input_direction(routinglist[routinglist.size() - 2], routinglist[routinglist.size() - 1]);
	out_d = 0;
	temp += (active_number[in_d][out_d] * L_SW_active(chip_temp[routinglist[0]], chip_temp[routinglist[routinglist.size() -1]]) + \
		passive_number[0][out_d] * L_SW_parking(chip_temp[routinglist[0]], chip_temp[routinglist[routinglist.size() - 1]]) + \
		crossing_number[0][out_d] * L_crossing);
	crossing_loss += crossing_number[in_d][out_d] * L_crossing;
	crossing_num += crossing_number[in_d][out_d];

	active_loss += active_number[in_d][out_d] * L_SW_active(chip_temp[routinglist[0]], chip_temp[routinglist[0]]);
	active_num += active_number[in_d][out_d];

	passive_loss += passive_number[in_d][out_d] * L_SW_parking(chip_temp[routinglist[0]], chip_temp[routinglist[0]]);
	passive_num += passive_number[in_d][out_d];

	if (temp == 0)
	{
		cout << "some is error" << endl;
	}
	return temp;
}

int RoutingData::get_input_direction(int src, int dst){

	switch (dst -src)
	{
	case 1:
		return 1;//EAST
	case -1:
		return 2;//WEST
	case 8:
		return 3;
	case -8:
		return 4;
	default:
		cout << "cal error" << endl;
		cout << src << "	" << dst << endl;
		break;
	}
	return 0;
}

int RoutingData::get_output_direaction(int src, int dst){
	switch (dst - src)
	{
	case 1:
		return 2;
	case -1:
		return 1;
	case 8:
		return 4;
	case -8:
		return 3;
	default:
		cout << "cal error" << endl;
		cout << src << "	" << dst << endl;
		break;
	}
}