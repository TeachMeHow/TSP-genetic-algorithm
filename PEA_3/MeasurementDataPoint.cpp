#include "MeasurementDataPoint.h"


MeasurementDataPoint::MeasurementDataPoint(std::chrono::milliseconds elapsed_time, int iteration_count, int solution_value)
{
	this->elapsed_time_ms = elapsed_time;
	this->iteration_count = iteration_count;
	this->solution_value = solution_value;
}

MeasurementDataPoint::~MeasurementDataPoint()
{
}

double MeasurementDataPoint::get_elapsed_time_ms()
{
	return (double)elapsed_time_ms.count();
}

int MeasurementDataPoint::get_iteration_count()
{
	return iteration_count;
}

int MeasurementDataPoint::get_solution_value()
{
	return solution_value;
}
