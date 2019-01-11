#include "MeasurementDataPoint.h"



MeasurementDataPoint::MeasurementDataPoint(std::chrono::milliseconds elapsed_time_ms, int gen_cnt, int mut_cnt, int solution_value)
{
	this->elapsed_time_ms = elapsed_time_ms;
	this->gen_cnt = gen_cnt;
	this->mut_cnt = mut_cnt;
	this->solution_value = solution_value;
}

MeasurementDataPoint::~MeasurementDataPoint()
{
}

std::string MeasurementDataPoint::to_string()
{
	std::string csv_row = std::string();
	csv_row += std::to_string(this->elapsed_time_ms.count());
	csv_row += ',';
	csv_row += std::to_string(gen_cnt);
	csv_row += ',';
	csv_row += std::to_string(mut_cnt);
	csv_row += ',';
	csv_row += std::to_string(solution_value);
	return csv_row;
}

int MeasurementDataPoint::get_value()
{
	return solution_value;
}

int MeasurementDataPoint::get_gen_cnt()
{
	return gen_cnt;
}

int MeasurementDataPoint::get_mut_cnt()
{
	return mut_cnt;
}

int MeasurementDataPoint::get_elapsed_time_ms()
{
	return elapsed_time_ms.count();
}
