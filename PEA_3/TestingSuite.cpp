#include "TestingSuite.h"
#include "ATSP.h"
#include "GeneticAlgorithm.h"



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
	
	const int POPULATION_SIZE[3] = { 5, 10, 20 };
	for (int i = 0; i < 3; i++)
	{
		/*/
		{
			ATSP small_problem = ATSP();
			small_problem.read_file("ftv47.atsp");
			GeneticAlgorithm ga = GeneticAlgorithm(20, 0.01, 0.8, POPULATION_SIZE[i]);
			int ms = std::chrono::duration_cast<std::chrono::milliseconds>(small_file_test_time).count();
			StopCondition condition = StopCondition(ms, 0);
			ga.run(&small_problem, &condition);
		}
		/*/
		/*
		{
			GeneticAlgorithm ga = GeneticAlgorithm(20, 0.01, 0.8, POPULATION_SIZE[i]);
			int ms = std::chrono::duration_cast<std::chrono::milliseconds>(medium_file_test_time).count();
			StopCondition condition = StopCondition(ms, 0);
			ga.run(&medium_problem, &condition);
		}
		*/
		//*
		{
			GeneticAlgorithm ga = GeneticAlgorithm(20, 0.01, 0.8, POPULATION_SIZE[i]);
			int ms = std::chrono::duration_cast<std::chrono::milliseconds>(large_file_test_time).count();
			StopCondition condition = StopCondition(ms, 0);
			ga.run(&large_problem, &condition);
		}
		//*/
		
	}

}