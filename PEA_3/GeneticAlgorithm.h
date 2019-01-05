#pragma once
#include "ATSP.h"
#include "Solution.h"
#include "StopCondition.h"
class GeneticAlgorithm
{
private:
	// parameters - size, mutation p, crossover method, mutation method, ptr to ATSP
	int population_size;
	double mutation_p;
	int problem_size;
	int selection_size;

	// best solution, mutation, iteration count, time
	const ATSP * problem;
	// ptr to stop condition
private:
	// select 
	std::vector<Solution> FP_selection(std::vector<Solution> * population);
	std::vector<Solution> initial_population();
public:
	GeneticAlgorithm(int population_size, double mutation_probability, int selection_size);
	~GeneticAlgorithm();
	void run(const ATSP * problem, StopCondition * stop_condition);
};

