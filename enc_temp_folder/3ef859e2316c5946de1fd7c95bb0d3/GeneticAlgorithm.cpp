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
		double total_distance = 0;
		double normalized_p = 0.0;
		std::vector<std::pair<Solution, double>> pairs;
		for (Solution p : *population)
		{
			double solution_value = p.get_value(*problem);
			solution_value = 1.0 / solution_value;
			total_distance += solution_value;
		}
		for (Solution p : *population)
		{
			double probability = p.get_value(*problem);
			probability = 1.0 / probability;
			probability /= total_distance;
			normalized_p += probability;
			pairs.push_back(std::pair<Solution, double>(p, normalized_p));
		}
		double random = rand();
		random /= RAND_MAX;
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
	return mating_pool;
}

std::vector<Solution> GeneticAlgorithm::TN_selection(std::vector<Solution>* population)
{
	int k = 5;
	double p = 0.9;
	std::vector<Solution> selection;
	// select k individuals
	while (selection.size() < 2)
	{
		std::vector<Solution> tournament;
		for (int i = 0; i < k; i++)
		{
			int random = rand() % (population->size() - 2);
			random += 1;
			tournament.push_back(*(population->begin() + random));
		}
		std::sort(tournament.begin(), tournament.end(), [&](const Solution & sol1, const Solution & sol2) { return sol1.get_value(*problem) < sol2.get_value(*problem); });
		for (int i = 0; i < tournament.size(); i++)
		{
			double random = rand();
			random /= (double)INT_MAX;
			double probability = p * (std::pow(1.0 - p, i));
			if (random < probability)
			{
				selection.push_back(tournament[i]);
			}

		}
	}
	return selection;
}

std::vector<Solution> GeneticAlgorithm::BEST_selection(std::vector<Solution>* population)
{
	std::vector<Solution> selection;
	while (selection.size() < 15)
	{
		int best_val = INT_MAX;
		auto best_solution = population->begin();
		for (auto it = population->begin(); it != population->end(); it++)
		{
			int val = it->get_value(*problem);
			if (val < best_val)
			{
				best_solution = it;
				best_val = val;
			}
		}
		selection.push_back(*best_solution);
		population->erase(best_solution);
	}
	return selection;
}

std::vector<Solution> GeneticAlgorithm::initial_population()
{
	std::vector<Solution> population;
	
	while (population.size() < initial_population_size)
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
			mut_cnt++;
		}
	}
}

void GeneticAlgorithm::PX_crossover(std::vector<Solution> * mating_pool, std::vector<Solution> * new_population)
{
	int pool_size = mating_pool->size();
	auto it1 = mating_pool->begin();
	// check all mating pool combinations
	for (it1; it1 != mating_pool->end(); it1++)
	{
		auto it2 = it1;
		for (it2; it2 != mating_pool->end(); it2++)
		{
			if (it1 != it2)
			{
				// get random value and do a crossover with probability crossover_p
				double random = rand();
				random /= RAND_MAX;
				if (random < crossover_p)
				{
					// get paths and trim front and back zeroes
					std::vector<int> p = (*it1).get_path();
					std::vector<int> q = (*it2).get_path();
					p.pop_back();
					p.erase(p.begin());
					q.pop_back();
					q.erase(q.begin());

					// 1.
					// get two indexes for PMX crossover
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

					// create two vectors with indexes ending at i_s - 1
					std::vector<int> r = std::vector<int>(i_s);
					std::vector<int> s = std::vector<int>(i_s);

					// pairs of <p_i, q_i>
					std::vector<std::pair<int, int>> swap_table;

					// TODO how does that happen - copies from [12], [13] is same as 12
					// swap range [i_s, i_e) from q to r
					r.insert(r.end(), q.begin() + i_s, q.begin() + i_e + 1);
					r.insert(r.end(), q.size() - 1 - i_e, 0);

					// swap range [i_s, i_e) from p to s
					s.insert(s.end(), p.begin() + i_s, p.begin() + i_e + 1);
					s.insert(s.end(), p.size() - 1 - i_e, 0);
					
					// fill swap table
					auto p_iter = p.begin() + i_s;
					auto q_iter = q.begin() + i_s;
					for (p_iter, q_iter; 
						p_iter != p.begin() + i_e + 1 && q_iter != q.begin() + i_e + 1; 
						p_iter++, q_iter++)
					{
						swap_table.emplace_back(*p_iter, *q_iter);
					}

					// 2.
					for (int i = i_s; i < i_e + 1; i++)
					{
						int value = p[i];
						int ind = i;
						if (std::find(r.begin() + i_s, r.begin() + i_e + 1, value) == r.begin() + i_e + 1)
						{
							int q_value;
						step_i:
							// i
							q_value = q[ind];
							// ii
							ind = 0;
							while (p[ind] != q_value)
							{
								ind++;
							}
							// iii
							if (ind >= i_s && ind <= i_e)
							{
								goto step_i;
							}
							// iv
							r[ind] = value;
						}
					}
					for (int i = i_s; i < i_e + 1; i++)
					{
						int value = q[i];
						int ind = i;
						if (std::find(s.begin() + i_s, s.begin() + i_e + 1, value) == s.begin() + i_e + 1)
						{
							int p_value;
						step_j:
							// i
							p_value = p[ind];
							// ii
							ind = 0;
							while (q[ind] != p_value)
							{
								ind++;
							}
							// iii
							if (ind >= i_s && ind <= i_e)
							{
								goto step_j;
							}
							// iv
							s[ind] = value;
						}
					}
					// 3.
					for (auto r_iter = r.begin(), p_iter = p.begin();
						r_iter != r.end();
						r_iter++, p_iter++)
					{
						if (*r_iter == 0)
						{
							*r_iter = *p_iter;
						}
					}
					for (auto s_iter = s.begin(), q_iter = q.begin();
						s_iter != s.end();
						s_iter++, q_iter++)
					{
						if (*s_iter == 0)
						{
							*s_iter = *q_iter;
						}
					}


					// insert zero front and back
					r.insert(r.begin(), 0);
					r.push_back(0);
					s.insert(s.begin(), 0);
					s.push_back(0);

					// add two children to population
					new_population->emplace_back(r);
					new_population->emplace_back(s);
					
				}
			}
		}
	}
	/*
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
	*/
}

void GeneticAlgorithm::find_best_solution(std::vector<Solution>* population)
{
	int best_found_value = INT_MAX;
	Solution best_found;
	for (Solution sol : *population)
	{
		int value = sol.get_value(*problem);
		if (value < best_found_value)
		{
			best_found = sol;
			best_found_value = value;
		}
	}
	if (best_found_value < best_solution.get_value(*problem))
	{
		best_solution = best_found;
	}
}

GeneticAlgorithm::GeneticAlgorithm(int population_size, double mutation_probability, double crossover_probability, int selection_size)
{
	this->initial_population_size = population_size;
	this->mutation_p = mutation_probability; 
	this->selection_size = selection_size;
	this->crossover_p = crossover_probability;
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
		std::vector<Solution> mating_pool = BEST_selection(&population);
		//std::vector<Solution> mating_pool = FP_selection(&population);
		//std::vector<Solution> mating_pool = TN_selection(&population);
		//crossover - populate population with population_size number of children
		std::vector<Solution> new_population;
		PX_crossover(&mating_pool, &new_population);
		//mutate
		inv_mutation(&new_population);
#ifdef DEBUG
		long total = 0;
		for (Solution sol : population)
		{
			total += sol.get_value(*problem);
		}
		long average = total;
		average = total / population.size();
		std::cout << "Generation " << gen_cnt << " average: " << average << std::endl;
#endif
		// find best solution from new population
		find_best_solution(&new_population);
		// population is new population now
		population = new_population;
		gen_cnt++;
	}
}

void GeneticAlgorithm::print_best_solution()
{
	std::cout << "Best solution: " << best_solution.get_value(*problem) << std::endl;
	std::cout << "Total generations: " << gen_cnt << std::endl;
	std::cout << "Total mutations: " << mut_cnt << std::endl;
}
