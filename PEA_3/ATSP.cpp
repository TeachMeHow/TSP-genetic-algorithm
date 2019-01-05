#include "ATSP.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <random> // for random number generation
#include <iomanip>
#include <stdexcept>


using namespace std;

void ATSP::parse_header_line(std::string & line)
{
	int pos = 0;
	string to_erase;
	if ((pos = line.find(to_erase = "NAME: ")) != string::npos) {
		line.erase(pos, to_erase.length());
		this->name = line;
	}
	else if ((pos = line.find(to_erase = "TYPE: ")) != string::npos) {
		line.erase(pos, to_erase.length());
		this->type = line;
	}
	else if ((pos = line.find(to_erase = "COMMENT: ")) != string::npos) {
		line.erase(pos, to_erase.length());
		this->comment = line;
	}
	else if ((pos = line.find(to_erase = "DIMENSION: ")) != string::npos) {
		line.erase(pos, to_erase.length());
		this->dimension = stoi(line);
	}
	else if ((pos = line.find(to_erase = "EDGE_WEIGHT_FORMAT: ")) != string::npos) {
		line.erase(pos, to_erase.length());
		this->comment = line;
	}
}


ATSP::ATSP()
{
}


ATSP::~ATSP()
{
}

void ATSP::read_file(string filename)
{
	string path_to_files = "matrices/";
	filename = path_to_files.append(filename);
	// remove previous matrix
	matrix.clear();

	//open file
	ifstream file;
	file.open(filename);

	// if file is open, read contents and close file
	if (file.is_open())
	{
		string line = "";
		while (line.find("EDGE_WEIGHT_SECTION") == string::npos) {
			getline(file, line);
			parse_header_line(line);
		}
		// read N lines, where N is size of the problem
		line = "";
		vector<int> row = vector<int>();
		while (line.find("EOF") == string::npos)
		{
			// read line
			getline(file, line);
			if (line.find("EOF") == string::npos)
			{
				// split line into tokens
				stringstream line_ss(line);
				string value;
				while (line_ss >> value)
				{
					row.push_back(stoi(value));
					if (row.size() == dimension)
					{
						matrix.push_back(row);
						row.clear();
					}
				}
			}

		}
		//close file
		file.close();
	}
	// if file is not opened, give error message
	else
	{
		cerr << "File could not not be opened";
	}

}

void ATSP::generate_random(int size)
{
	using namespace std;
	matrix.clear();
	random_device seed;
	mt19937 gen(seed());
	uniform_int_distribution<int> dist(0, 100);
	for (size_t i = 0; i < size; i++)
	{
		vector<int> row;
		for (size_t j = 0; j < size; j++)
		{
			int random_int = dist(gen);
			row.push_back(random_int);
		}
		matrix.push_back(row);
	}
	for (size_t i = 0; i < size; i++)
	{
		matrix[i][i] = -1;
	}
}

void ATSP::print_data()
{
	cout << "Size: " << matrix.size() << endl;
	int row_cnt = 0;
	for (vector<int>& row : matrix)
	{
		if (row_cnt < 10)
		{
			int col_cnt = 0;
			for (int val : row)
			{
				if (col_cnt < 20)
				{
					cout << setw(5) << setiosflags(ios::left) << val;
					col_cnt++;
				}
			}
			row_cnt++;
			cout << endl;
		}
	}
}

int ATSP::get_distance(int y, int x) const
{
	if (y < 0 || y >= dimension || x < 0 || x >= dimension){
		throw out_of_range("Index out of range, argument range is 0..." 
			+ to_string(dimension - 1));
	}
	return matrix[y][x];
}

int ATSP::get_size() const
{
	return dimension;
}

std::vector<std::vector<int>> ATSP::get_matrix()const
{
	return matrix;
}
