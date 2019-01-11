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

#define PERFORMANCE 0
//#define MENU 0
//#define DEBUG 0


int main() {
#ifdef PERFORMANCE
	TestingSuite suite;
	suite.run_tests();
#endif
#ifdef DEBUG
	ATSP problem;
	problem.read_file("ftv47.atsp");
	GeneticAlgorithm algorithm = GeneticAlgorithm(20, 0.01, 0.8, 5);
	StopCondition stop_condition = StopCondition(120 * 1000, 0);
	algorithm.run(&problem, &stop_condition);
	algorithm.print_best_solution();
#endif
#ifdef MENU
	ATSP problem = ATSP();
	menu_loop(problem);
#endif
	return 0;
}


