#include "Solution.h"

//#define DEBUG 0 




Solution::Solution()
{
	path = std::vector<int>();
}

Solution::Solution(std::vector<int> path)
{
	set_path(path);
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
	int value = INT_MAX;
	if (!path.empty())
	{
		value = 0;
		auto first = path.cbegin();
		for (auto second = first + 1; second != path.cend(); second++)
		{
			value += graph.get_distance(*first, *second);
			first = second;
		}
	}
	return value;
}

void Solution::set_path(std::vector<int> path)
{
	this->path = path;
#ifdef DEBUG
	auto first = path.cbegin();
	for (auto second = first + 1; second != path.cend(); second++)
	{
		if (*first == *second)
		{
			throw "Path incorrect";
		}
		first = second;
	}
#endif
}
