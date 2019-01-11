#include <chrono> // Wait for Exit
#include <thread> //
#include <iostream>
#include "Menu.h"
#include "ATSPSolver.h"
#include "GeneticAlgorithm.h"

using std::cout;
using std::endl;
using std::cin;
const char* MENU =
"Wybierz akcje:\n"
"1. Wczytaj z pliku\n"
"2. Wyswietl dane\n"
"3. Uruchom algorytm i wyswietl wynik\n"
"q. Wyjdz z programu\n";

void menu_loop(ATSP& problem)
{
	char choice;

	cout << MENU << endl;
	while (cin >> choice)
	{
		system("CLS");
		if (!_call(choice, problem)) break;
		system("CLS");
		cout << MENU << endl;
	}

}

// call function for menu
bool _call(char x, ATSP& problem)
{
	int i_x = x - 0x30;
	std::string filename;
	int i;
	int method;
	int initial_population;
	double m_p;
	double x_p;
	int population;
	int time;
	int iterations; 
	GeneticAlgorithm * algo = nullptr;
	switch (i_x)
	{
	case 1: cout << "Nazwa pliku: ";
		cin >> filename;
		problem.read_file(filename);
		break;
	case 2: problem.print_data();
		system("pause");
		break;
	case 3: cout << "Wybierz metode: \n1. PMX \n2. OX";
		cin >> method;
		cout << "Licznosc populacji poczatkowej: ";
		cin >> initial_population;
		cout << "Prawdopodobienstwo mutacji: ";
		cin >> m_p;
		cout << "Prawdopodobienstwo krzyzowania";
		cin >> x_p;
		cout << "Licznosc populacji: ";
		cin >> population;
		cout << "Kryterium stopu: \n1. Czas (ms) \n2. Iteracje";
		cin >> i;
		if (i == 1)
		{
			cin >> time;
			iterations = 0;
		}
		else if (i == 2)
		{
			cin >> iterations;
			time = 0;
		}
		algo = new GeneticAlgorithm(initial_population, m_p, x_p, population);
		algo->run(&problem, &StopCondition(time, iterations));
		algo->print_best_solution();
		
		cout << endl;
		system("pause");
		break;
	case 'q' - 0x30:
		cout << "Exiting...";
		std::this_thread::sleep_for(std::chrono::seconds(1));
		return false;
	default: break;
	}
	if (algo != nullptr)
		delete algo;
	return true;
}


void print_solution(ATSP& problem, Solution & solution)
{
	cout << "Rozwiazanie: " << solution.get_value(problem) << endl;
	const int max_row_width = 20;
	int row_width = 0;
	for (int v : solution.get_path())
	{
		if (row_width > max_row_width)
		{
			cout << endl;
			row_width = 0;
		}
		row_width++;
		cout << v << "-";
	}
}
