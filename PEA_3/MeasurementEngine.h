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
	std::chrono::milliseconds best_value_first_occurence;
	int best_value = INT_MAX;
public:
	MeasurementEngine();
	~MeasurementEngine();
	// get state of condition and current best value
	void poll(const StopCondition & condition, int best_solution_value);
	// prints to csv file
	// problem size is here to determine best known solution for example files
	void print_to_csv_file(const char * filename);
	std::chrono::milliseconds get_best_value_first_occurence() const;
	int get_best_value() const;
};

