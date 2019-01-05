#pragma once
#include "ATSP.h"
#include <vector>
#include <list>
#include "TestingSuite.h"
class ATSPSolver
{
private:
	void print_solution(ATSP& problem, Solution & solution);
	TestingSuite * testing_suite;
public:
	ATSPSolver();
	ATSPSolver(TestingSuite *);
	~ATSPSolver();
	Solution nearest_neighbor(ATSP& atsp);
	Solution random_solution(ATSP & atsp);
	//void simulated_anneal(ATSP& atsp, std::vector<int>& solution);
};

