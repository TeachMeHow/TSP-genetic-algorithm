#include "TestingSuite.h"
#include "ATSP.h"
#include "ATSPSolver.h"



TestingSuite::TestingSuite()
{
}


TestingSuite::~TestingSuite()
{
}

void TestingSuite::run_tests()
{
	ATSP small_problem = ATSP();
	ATSP medium_problem = ATSP();
	ATSP large_problem = ATSP();
	small_problem.read_file("ftv47.atsp");
	medium_problem.read_file("ftv170.atsp");
	large_problem.read_file("rbg403.atsp");
	ATSPSolver solver = ATSPSolver(this);
	int runs = 1;
	Solution small_problem_initial_solution = solver.nearest_neighbor(small_problem);
	Solution medium_problem_initial_solution = solver.nearest_neighbor(medium_problem);
	Solution large_problem_initial_solution = solver.nearest_neighbor(large_problem);

	Solution buffer;
	for (int i = 0; i < runs; i++)
	{
	}

	std::ofstream file;
	file.open("test_results.csv", std::ios::out | std::ios::trunc);
	file << "Best small file result,Best medium file result,Best large file result\n";
	file << small_file_best_value << "," << medium_file_best_value << "," << large_file_best_value << "\n";
	file << "Found after (ms),,\n";
	file << small_file_best_elapsed_time.count() << "," << medium_file_best_elapsed_time.count() << "," << large_file_best_elapsed_time.count() << "\n";
	file << "Best path,,\n";
	std::string row;
	std::string s_path;
	for (int v : small_file_best_solution.get_path())
	{
		s_path.append(std::to_string(v));
		s_path.append("->");
	}
	row.append(s_path);
	row.append(",");
	for (int v : medium_file_best_solution.get_path())
	{
		s_path.append(std::to_string(v));
		s_path.append("->");
	}
	row.append(s_path);
	row.append(",");
	for (int v : large_file_best_solution.get_path())
	{
		s_path.append(std::to_string(v));
		s_path.append("->");
	}
	row.append(s_path);
	row.append("\n");
	file << row;
	file.close();
}

void TestingSuite::check_best(Solution solution, const MeasurementEngine & poller)
{
	int value = poller.get_best_value();
	if (small_file_best_value > value && solution.get_path().size() < 100)
	{
		small_file_best_solution = solution;
		small_file_best_value = value;
		small_file_best_elapsed_time = poller.get_best_value_first_occurence();
	}

	else if (medium_file_best_value > value && 100 < solution.get_path().size() && solution.get_path().size() < 200)
	{
		medium_file_best_solution = solution;
		medium_file_best_value = value;
		medium_file_best_elapsed_time = poller.get_best_value_first_occurence();
	}

	else if (large_file_best_value > value && solution.get_path().size() > 200)
	{
		large_file_best_solution = solution;
		large_file_best_value = value;
		large_file_best_elapsed_time = poller.get_best_value_first_occurence();
	}

}
