#include "ATSPSolver.h"
#include "StopCondition.h"
#include "MeasurementEngine.h"
#include <iostream> // for testing purposes


void ATSPSolver::print_solution(ATSP& problem, Solution & solution)
{
	std::cout << "Rozwiazanie: " << solution.get_value(problem) << std::endl;
	const int max_row_width = 20;
	int row_width = 0;
	for (int v : solution.get_path())
	{
		if (row_width > max_row_width)
		{
			row_width = 0;
		}
		row_width++;
		std::cout << v << "-";
	}
}

ATSPSolver::ATSPSolver()
{
	srand(time(NULL)); 
	testing_suite = nullptr;
}

ATSPSolver::ATSPSolver(TestingSuite * testing_suite) : ATSPSolver()
{
	this->testing_suite = testing_suite;
}


ATSPSolver::~ATSPSolver()
{
}

Solution ATSPSolver::nearest_neighbor(ATSP & atsp)
{
	std::set<int> unvisited_vertices = std::set<int>();
	for (int i = 1; i < atsp.get_size(); i++)
	{
		unvisited_vertices.insert(i);
	}
	std::vector<int> path = std::vector<int>();
	path.push_back(0);
	while (!unvisited_vertices.empty())
	{
		int min_distance = INT_MAX;
		int last = *(path.end() - 1);
		int next;
		for (int v : unvisited_vertices)
		{
			int distance = atsp.get_distance(last, v);
			if (distance < min_distance)
			{
				min_distance = distance;
				next = v;
			}
		}
		unvisited_vertices.erase(next);
		path.push_back(next);
	}
	path.push_back(0);
	return Solution(path);
}

Solution ATSPSolver::random_solution(ATSP & atsp)
{
	std::vector<int> path = std::vector<int>();
	int random_index;
	std::vector<int> unvisited_vertices = std::vector<int>();
	for (int v = 1; v < atsp.get_size(); v++)
	{
		unvisited_vertices.push_back(v);
	}
	path.push_back(0);
	while (!unvisited_vertices.empty())
	{
		random_index = rand() % unvisited_vertices.size();
		path.push_back(unvisited_vertices[random_index]);
		unvisited_vertices.erase(unvisited_vertices.begin() + random_index);
	}
	path.push_back(0);
	return Solution(path);
}
