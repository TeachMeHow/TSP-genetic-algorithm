#include "StopCondition.h"


StopCondition::StopCondition(int ms_time_limit, int iteration_limit)
	: time_limit(std::chrono::milliseconds(ms_time_limit)), 
	iteration_limit(iteration_limit)
{
}

StopCondition::~StopCondition()
{
}

bool StopCondition::check()
{
	if (!active) reset();

	++iteration_counter;
	std::chrono::milliseconds elapsed_time;
	elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(clock.now() - check_start);
	// check time
	if (elapsed_time > time_limit && time_limit.count() != 0)
	{
		return true;
	}
	// check iterations
	if (iteration_counter > iteration_limit && iteration_limit != 0)
	{
		return true;
	}
	return false;

}

void StopCondition::reset()
{
	iteration_counter = 0;
	check_start = clock.now();
	active = true;
}

std::chrono::milliseconds StopCondition::get_elapsed_time() const
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(clock.now() - check_start);
}

int StopCondition::get_iteration_count() const
{
	return iteration_counter;
}
