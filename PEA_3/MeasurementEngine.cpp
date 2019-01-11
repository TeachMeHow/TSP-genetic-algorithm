#include "MeasurementEngine.h"



MeasurementEngine::MeasurementEngine()
{
}


MeasurementEngine::~MeasurementEngine()
{
}

void MeasurementEngine::poll(std::chrono::milliseconds elapsed_time, int gen_cnt, int mut_cnt, int best_val)
{
	data.emplace_back(elapsed_time, gen_cnt, mut_cnt, best_val);
}

void MeasurementEngine::print_to_csv_file(const char * filename)
{
	std::ofstream file;
	file.open(filename, std::ios::trunc | std::ios::out);
	file << "filename,Best solution,Generations,Mutations,Elapsed Time\n";
	file << filename << ',' << data.back().get_value() << ',' 
		<< data.back().get_gen_cnt() << ',' << data.back().get_mut_cnt() << ','
		<< data.back().get_elapsed_time_ms();

	file << "\nData\n";
	file << "Elapsed time (ms),Generation,Mutations,Best solution";
	for (MeasurementDataPoint data_point : data)
	{
		file << data_point.to_string();
		file << '\n';
	}
	file.close();
}