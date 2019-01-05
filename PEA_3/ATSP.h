#pragma once

#include <vector>
#include <set>
#include <string>
class ATSP
{
private:
	// graph matrix, y is from, x is to
	std::vector<std::vector<int>> matrix;
	// atsp properties
	std::string name;
	std::string type;
	std::string comment;
	// number of vertices in a graph
	int dimension;
	std::string edge_weight_format;

private:
	void parse_header_line(std::string& line);

public:
	ATSP();
	~ATSP();
	// creates graph matrix from .atsp file
	void read_file(std::string filename);
	// generates random atsp problem
	void generate_random(int size);
	// print part of the graph to console output
	void print_data();
	// get distance from vertice 'y' to 'x'
	int get_distance(int y, int x) const;
	// get size of the problem - number of vertices
	int get_size() const;
	std::vector<std::vector<int>> get_matrix() const;
};

