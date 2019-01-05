#include "Solution.h"






Solution::Solution()
{
	path = std::vector<int>();
}

Solution::Solution(std::vector<int> path)
{
	this->path = path;
}

Solution::Solution(const Solution & obj)
{
	this->path = std::vector<int>(obj.path);
}

Solution::~Solution()
{
}

std::vector<int> Solution::get_path() const
{
	return path;
}

int Solution::get_value(const ATSP & graph) const
{
	int value = 0;
	for (auto it = path.cbegin() + 1; it != path.cend(); it++)
	{
		value += graph.get_distance(*(it - 1), *it);
	}
	return value;
}

void Solution::set_path(std::vector<int> path)
{
	this->path = path;
}
