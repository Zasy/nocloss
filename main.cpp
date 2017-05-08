#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <assert.h>
#include <iterator>
#include "routing_data.h"
#include "defination.h"

using namespace std;
int main(int argc, char *argv[]){


	string input_file_name(argv[1]);
	string output_file_name(argv[2]);

	string parameter_file_name = "parameter.txt";
	ifstream parameter_fp;
	parameter_fp.open(parameter_file_name.c_str(), ios::in);
	assert(parameter_fp.is_open());
	parameter_fp >> T_0;
	parameter_fp >> lambda_VCSEL_0;
	parameter_fp >> lambda_MR_0_new;
	parameter_fp >> row_VCSEL;
	parameter_fp >> row_MR;
	parameter_fp >> delta;
	parameter_fp >> lambda_b;
	parameter_fp.close();

	ofstream loss_log;
	loss_log.open(output_file_name, ios::out | ios::app);

	ifstream input(input_file_name);
	string line1, line2;
	
	std::vector< std::vector<int>> all_integers;
	vector<int> one_integers;
	vector<int> routing_list;

	while (getline( input, line1) && getline( input, line2))
	{
		
		istringstream is1(line1);
		istringstream is2(line2);
		one_integers = vector<int>(istream_iterator<int>(is1), istream_iterator<int>());
		routing_list = vector<int>(istream_iterator<int>(is2), istream_iterator<int>());
		RoutingData test1(one_integers[0], one_integers[3], one_integers[1], one_integers[2], routing_list);
		/*
		istringstream is(line);
		all_integers.push_back(	vector<int>(istream_iterator<int>(is), istream_iterator<int>()));
		*/
		loss_log << test1.generate_time << "\t" << test1.receive_time << "\t" << test1.src << "\t" << test1.dest << "\t" << test1.getloss() \
			<<"\t" << test1.active_loss <<"\t" << test1.active_num << "\t" << test1.crossing_loss<<"\t" << test1.crossing_num << "\t" \
			<< test1.passive_loss << "\t" <<test1.passive_num;
		/*
		for ( int i = 0; i < routing_list.size(); i++)
		{
			loss_log << "\t" << routing_list[i];
		}
		*/
		loss_log << endl;
	}

	input.close();
	loss_log.close();

	return 0;
}