// This file contains declarations of some functions 
// that present the user with functionality of some data
// structures that were implemented by me in this project
//
// Author: Szymon Cichy 235093
// Date: March 2018
//
#pragma once
#include "ATSP.h"
#include "Solution.h"
void menu_loop(ATSP& problem);
bool _call(char x, ATSP& problem);
void print_solution(ATSP& problem, Solution & solution);