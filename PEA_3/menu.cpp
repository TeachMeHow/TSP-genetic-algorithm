#include <chrono> // Wait for Exit
#include <thread> //
#include <iostream>
#include "Menu.h"
#include "ATSPSolver.h"

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
	switch (i_x)
	{
	case 1: cout << "Nazwa pliku: ";
		cin >> filename;
		problem.read_file(filename);
		break;
	case 2: problem.print_data();
		system("pause");
		break;
	case 3: cout << "Wybierz metode: \n1. Nearest neighbor";
		cin >> i;
		if (i == 1) {
			Solution solution = ATSPSolver().nearest_neighbor(problem);
			print_solution(problem, solution);
		}
		cout << endl;
		system("pause");
		break;
	case 'q' - 0x30:
		cout << "Exiting...";
		std::this_thread::sleep_for(std::chrono::seconds(1));
		return false;
	default: break;
	}
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
