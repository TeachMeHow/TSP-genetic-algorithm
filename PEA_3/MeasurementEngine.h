#pragma once
#include "StopCondition.h"
#include "MeasurementDataPoint.h"
#include <vector>
#include <fstream>
// polls 
class MeasurementEngine
{
private:
	std::vector<MeasurementDataPoint> data;
private:
	int best_value = INT_MAX;
public:
	MeasurementEngine();
	~MeasurementEngine();
	// get state of condition and current best value
	void poll(std::chrono::milliseconds elapsed_time, int gen_cnt, int mut_cnt, int best_val);
	// prints to csv file
	// problem size is here to determine best known solution for example files
	void print_to_csv_file(const char * filename);
};

