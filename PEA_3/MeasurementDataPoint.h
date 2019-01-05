#pragma once
#include "Solution.h"
#include <chrono>
// containts measurement data for TSP algorithm
class MeasurementDataPoint
{
private: 
	std::chrono::milliseconds elapsed_time_ms;
	int iteration_count;
	int solution_value;
public:
	MeasurementDataPoint(std::chrono::milliseconds elapsed_time, int iteration_count , int solution_value);
	~MeasurementDataPoint();
	double get_elapsed_time_ms();
	int get_iteration_count();
	int get_solution_value();

};

