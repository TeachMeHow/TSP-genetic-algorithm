#pragma once
#include "Solution.h"
#include <chrono>
// containts measurement data for TSP algorithm
class MeasurementDataPoint
{
private: 
	std::chrono::milliseconds elapsed_time_ms;
	int gen_cnt;
	int mut_cnt;
	int solution_value;
public:
	MeasurementDataPoint(std::chrono::milliseconds elapsed_time_ms,
	int gen_cnt,
	int mut_cnt,
	int solution_value);
	~MeasurementDataPoint();
	// data point for csv file
	std::string to_string();
	int get_value();
	int get_gen_cnt();
	int get_mut_cnt();
	int get_elapsed_time_ms();
	

};

