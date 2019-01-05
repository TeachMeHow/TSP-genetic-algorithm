#pragma once
#include <chrono>
/* Check for stop condition every iteration */
class StopCondition
{
	bool active = false;
	const std::chrono::milliseconds time_limit;
	const int iteration_limit; 
	int iteration_counter; 
	std::chrono::time_point<std::chrono::high_resolution_clock> check_start;
	std::chrono::high_resolution_clock clock;
public:
	StopCondition(int ms_time_limit, int iteration_limit);
	~StopCondition();
	// checks if any condition is fulfilled, and returns true if it is
	// checks active to 
	bool check();
	// reset time flow and iteration
	void reset();
	std::chrono::milliseconds get_elapsed_time() const;
	int get_iteration_count() const;
};

