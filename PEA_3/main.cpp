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



int main() {

	//std::vector<int> vec = { 1 , 2 };
	//auto first = vec.begin() + 0;
	//auto last = vec.end() - 1;
	//vec.erase(first);
	//int second = *last;
	// initialize the problem
	ATSP problem;
	problem.read_file("ftv47.atsp");
	
	menu_loop(problem);
	TestingSuite suite;
	//suite.run_tests();
	return 0;
}


