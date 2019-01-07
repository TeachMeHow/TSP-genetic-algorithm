#include "GeneticAlgorithm.h"
#include <map>
#include <iostream>
#define DEBUG 0

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

void GeneticAlgorithm::inv_mutation(std::vector<Solution>* population)
{
	for (Solution & sol : *population)
	{
		double random = rand() / RAND_MAX;
		if (random < mutation_p)
		{
			auto path = sol.get_path();
			int i_s = 0;
			int i_e = 0;
			while (i_s == i_e)
			{
				i_s = rand() % (path.size() - 2);
				i_e = rand() % (path.size() - 2);
				if (i_s > i_e)
				{
					int buf = i_s;
					i_s = i_e;
					i_e = buf;
				}
			}
			i_s++;
			i_e++;
			std::reverse(path.begin() + i_s, path.begin() + i_e + 1);
			sol.set_path(path);
		}
	}
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
		new_population.push_back(mating_pool.front());
#ifdef DEBUG
		std::cout << '\n';
		for (int v : new_population.front().get_path())
		{
			std::cout << '.' << v;
		}
#endif // DEBUG

		//mutate
		inv_mutation(&new_population);
#ifdef DEBUG
		std::cout << '\n';
		for (int v : new_population.front().get_path())
		{
			std::cout << '.' << v;
		}
#endif // DEBUG

	}
}
