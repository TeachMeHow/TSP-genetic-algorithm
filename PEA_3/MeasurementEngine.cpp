#include "MeasurementEngine.h"



MeasurementEngine::MeasurementEngine()
{
}


MeasurementEngine::~MeasurementEngine()
{
}

void MeasurementEngine::poll(const StopCondition & condition, int best_solution_value)
{
	auto elapsed_time_ms = condition.get_elapsed_time();
	int iteration_count = condition.get_iteration_count();
	MeasurementDataPoint data_point = MeasurementDataPoint(elapsed_time_ms, iteration_count, best_solution_value);
	data.push_back(data_point);
	if (best_solution_value < best_value)
	{
		best_value = best_solution_value;
		best_value_first_occurence = elapsed_time_ms;
	}
}

void MeasurementEngine::print_to_csv_file(const char * filename)
{
	std::ofstream file;
	file.open(filename, std::ios::trunc | std::ios::out);
	file << "filename,Best solution,Best solution found at (ms)\n";
	file << filename << ',' << best_value << ',' << best_value_first_occurence.count() << '\n';
	file << "Data,,\n";
	file << "Best solution,Elapsed Time (ms),Iteration\n";
	for (MeasurementDataPoint data_point : data)
	{
		file << data_point.get_solution_value() << ','
			<< data_point.get_elapsed_time_ms() << ','
			<< data_point.get_iteration_count() << '\n';
	}
	file.close();
}

std::chrono::milliseconds MeasurementEngine::get_best_value_first_occurence() const
{
	return best_value_first_occurence;
}

int MeasurementEngine::get_best_value() const
{
	return best_value;
}
