#pragma once
#include "ATSP.h"
#include "Solution.h"
#include "StopCondition.h"
class GeneticAlgorithm
{
private:
	// parameters - size, mutation p, crossover method, mutation method, ptr to ATSP
	int initial_population_size;
	double mutation_p;
	double crossover_p;
	int problem_size;
	int selection_size;

	// best solution, mutation, iteration count, time
	const ATSP * problem;

	// generation count
	int gen_cnt;
	// mutation count;
	int mut_cnt;
	// best solution
	Solution best_solution;
private:
	// select 
	std::vector<Solution> FP_selection(std::vector<Solution> * population);
	std::vector<Solution> TN_selection(std::vector<Solution>* population);
	std::vector<Solution> BEST_selection(std::vector<Solution> * population);
	std::vector<Solution> initial_population();
	void inv_mutation(std::vector<Solution> * population);
	// populates new population using chromosomes from mating pool, with probability of crossover_p
	// crossover_p - 1 = every member with every member, 0 - every member with noone
	void PX_crossover(std::vector<Solution> * mating_pool, std::vector<Solution> * new_population);
	void OX_crossover(std::vector<Solution> * mating_pool, std::vector<Solution> * new_population);
	void find_best_solution(std::vector<Solution> * population);
public:
	GeneticAlgorithm(int population_size, double mutation_probability, double crossover_probability, int selection_size);
	~GeneticAlgorithm();
	void run(const ATSP * problem, StopCondition * stop_condition);
	void print_best_solution();
};

