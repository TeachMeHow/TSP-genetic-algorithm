#pragma once
#include <chrono>
#include "MeasurementEngine.h"
class TestingSuite
{
private:
	
	const std::chrono::seconds small_file_test_time = std::chrono::seconds(120);
	const std::chrono::minutes medium_file_test_time = std::chrono::minutes(4);
	const std::chrono::minutes large_file_test_time = std::chrono::minutes(6);
	
	/*
	const std::chrono::seconds small_file_test_time = std::chrono::seconds(5);
	const std::chrono::seconds medium_file_test_time = std::chrono::seconds(5);
	const std::chrono::seconds large_file_test_time = std::chrono::seconds(5);
	*/

public:
	TestingSuite();
	~TestingSuite();
	void run_tests();
};

