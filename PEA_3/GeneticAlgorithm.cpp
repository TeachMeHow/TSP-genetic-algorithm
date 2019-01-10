#include "GeneticAlgorithm.h"
#include <map>
#include <iostream>
#include <algorithm>
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
				population->erase(std::find(population->cbegin(), population->cend(), pair.first));
				break;
			}

		}

	}
#ifdef DEBUG
	for (Solution sol : mating_pool)
	{
		auto path = sol.get_path();
		for (int ver : path)
		{
			std::cout << "." << ver;
		}
		std::cout << "\n";

	}
#endif // DEBUG
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
/*#ifdef DEBUG
		for (int ver : path)
		{
			std::cout << "." << ver;
		}
		std::cout << "\n";
#endif // DEBUG*/
		population.emplace_back(path);
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

void GeneticAlgorithm::PX_crossover(Solution * p_solution, Solution * q_solution, Solution * r_solution, Solution * s_solution)
{
	std::vector<int> p = p_solution->get_path();
	std::vector<int> q = q_solution->get_path();
	p.pop_back();
	p.erase(p.begin());
	q.pop_back();
	q.erase(q.begin());
	std::vector<int> r = std::vector<int>(p.size());
	std::vector<int> s = std::vector<int>(q.size());

	int i_s = 0;
	int i_e = 0;
	while (i_s == i_e)
	{
		i_s = rand() % q.size();
		i_e = rand() % q.size();
		if (i_s > i_e)
		{
			int buf = i_s;
			i_s = i_e;
			i_e = buf;
		}
	}
	std::vector<std::pair<int, int>> swap_table;
	for (int i = i_s; i <= i_e; i++)
	{
		r[i] = q[i];
		s[i] = p[i];
		swap_table.emplace_back(p[i], q[i]);
	}
	for (int i = 0; i < r.size(); i++)
	{
		if (i >= i_s && i <= i_e) 
			continue;
		int swap_val = p[i];
		auto ind = std::find_if(swap_table.cbegin(), swap_table.cend(), [&swap_val](const std::pair<int, int>& element) { return element.second == swap_val; });
		if (ind == swap_table.cend())
		{
			r[i] = swap_val;
		}
		else
		{
			r[i] = (*ind).first;
		}
		swap_val = q[i];
		ind = std::find_if(swap_table.cbegin(), swap_table.cend(), [&swap_val](const std::pair<int, int>& element) { return element.first == swap_val; });
		if (ind == swap_table.cend())
		{
			s[i] = swap_val;
		}
		else
		{
			s[i] = (*ind).second;
		}
	}
	std::vector<int> r_path;
	std::vector<int> s_path;
	r_path.push_back(0);
	for (int elem : r)
	{
		r_path.push_back(elem);
	}
	r_path.push_back(0);
	s_path.push_back(0);
	for (int elem : s)
	{
		s_path.push_back(elem);
	}
	s_path.push_back(0);
	r_solution->set_path(r_path);
	s_solution->set_path(s_path);
}

GeneticAlgorithm::GeneticAlgorithm(int population_size, double mutation_probability, int selection_size)
{
	this->population_size = population_size;
	this->mutation_p = mutation_probability; 
	this->selection_size = selection_size;
	srand(time(NULL));
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
		Solution c_1;
		Solution c_2;
		PX_crossover(&mating_pool[0], &mating_pool[1], &c_1, &c_2);
		new_population.push_back(c_1);
		new_population.push_back(c_2);
		//mutate
		inv_mutation(&new_population);
	}
}
