#include "GeneticAlgorithm.h"
#include <map>


std::vector<Solution> GeneticAlgorithm::FP_selection(std::vector<Solution>* population)
{
	std::vector<Solution> mating_pool;
	while (mating_pool.size() < selection_size)
	{
		int total_distance = 0;
		double normalized_p = 0.0;
		std::vector<std::pair<Solution, double>> pairs;
		for (Solution p : *population)
		{
			int solution_value = p.get_value(*problem);
			total_distance += solution_value;
		}
		for (Solution p : *population)
		{
			double probability = p.get_value(*problem);
			probability /= total_distance;
			normalized_p += probability;
			pairs.push_back(std::pair<Solution, double>(p, normalized_p));
		}
		double random = rand() / RAND_MAX;
		for (std::pair<Solution, double> pair : pairs)
		{
			if (random < pair.second)
			{
				mating_pool.push_back(pair.first);
				break;
			}

		}

	}
	return mating_pool;
}

std::vector<Solution> GeneticAlgorithm::initial_population()
{
	std::vector<Solution> population;
	
	for (int i = 0; i < population_size; i++)
	{
		std::vector<int> path = std::vector<int>();
		int random_index;
		std::vector<int> unvisited_vertices = std::vector<int>();
		for (int v = 1; v < problem_size; v++)
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
		population.emplace_back(Solution(path));
	}
	return population;
}

GeneticAlgorithm::GeneticAlgorithm(int population_size, double mutation_probability, int selection_size)
{
	this->population_size = population_size;
	this->mutation_p = mutation_probability; 
	this->selection_size = selection_size;
	srand(NULL);
}

GeneticAlgorithm::~GeneticAlgorithm()
{
}

void GeneticAlgorithm::run(const ATSP * problem, StopCondition * stop_condition)
{
	this->problem_size = problem->get_size();
	this->problem = problem;
	std::vector<Solution> population = initial_population();
	while (!stop_condition->check())
	{
		
		// select from population
		std::vector<Solution> mating_pool = FP_selection(&population);
		//crossover - populate population with population_size number of children
		std::vector<Solution> new_population;

		//mutate
		for (Solution gene : new_population)
		{
			double result = rand() / RAND_MAX;
			if (result < mutation_p)
			{
				/*
				ref to gene!
				mutate(gene);
				*/
			}
			// random
		}
	}
}
