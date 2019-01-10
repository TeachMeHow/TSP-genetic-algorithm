#include "Menu.h"
#include "ATSP.h"
#include "Solution.h"
#include "ATSPSolver.h"
#include "StopCondition.h"
#include <iostream>;
#include <vector>
#include <iomanip>
#include <algorithm>
#include "TestingSuite.h"
#include "GeneticAlgorithm.h"


int main() {

	//std::vector<int> vec = { 1 , 2 };
	//auto first = vec.begin() + 0;
	//auto last = vec.end() - 1;
	//vec.erase(first);
	//int second = *last;
	// initialize the problem
	ATSP problem;
	problem.read_file("ftv47.atsp");
	GeneticAlgorithm algorithm = GeneticAlgorithm(20, 0.01, 0.9, 5);
	StopCondition stop_condition = StopCondition(60 * 1000, 0);
	algorithm.run(&problem, &stop_condition);
	algorithm.print_best_solution();
	menu_loop(problem);
	TestingSuite suite;
	//suite.run_tests();
	return 0;
}


