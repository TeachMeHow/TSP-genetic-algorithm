#pragma once
#include <chrono>
#include "MeasurementEngine.h"
class TestingSuite
{
private:
	const std::chrono::seconds small_file_test_time = std::chrono::seconds(120);
	const std::chrono::minutes medium_file_test_time = std::chrono::minutes(4);
	const std::chrono::minutes large_file_test_time = std::chrono::minutes(6);
	Solution small_file_best_solution;
	std::chrono::milliseconds small_file_best_elapsed_time;
	int small_file_best_value = INT_MAX;
	Solution medium_file_best_solution;
	std::chrono::milliseconds medium_file_best_elapsed_time;
	int medium_file_best_value = INT_MAX;
	Solution large_file_best_solution;
	std::chrono::milliseconds large_file_best_elapsed_time;
	int large_file_best_value = INT_MAX;

public:
	TestingSuite();
	~TestingSuite();
	void run_tests();
	void check_best(Solution solution, const MeasurementEngine & poller);
};

