/*Part 1 of day 6, AoC 2019
Author(s)		: Lukas Mirow
Date of creation	: 9/28/2021
*/

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <cstdlib>
#include <utility>
#include <sstream>
#include "tree.hpp"
using namespace std;

//Print error and abort
void err(const char *msg)
{
	cerr << msg << endl;
	exit(EXIT_FAILURE);
}

//Trim
string trim(string in)
{
	size_t first = in.find_first_not_of(" \t\n");
	size_t last = in.find_last_not_of(" \t\n");
	return in.substr(first, last - first + 1);
}

//Split input line into names of planets
pair<string,string> split_input(const string input)
{
	string first = input.substr(0, input.find(')'));
	string second = input.substr(input.find(')') + 1);
	return pair<string,string>(trim(first), trim(second));
}

int main(int argc, char **argv)
{

	//Open file
	ifstream f;
	f.open("in1.txt");
	if (!f.is_open())
		err("Error opening file");

	//Create tree and node table from file
	map<string,Node> nodes;
	string line;
	while (getline(f, line))
	{

		//Pre-process input
		pair<string,string> inputs = split_input(line);

		//Create left-hand node if it does not exist yet
		if (nodes.find(inputs.first) == nodes.end())
			nodes.insert(pair<string,Node>(inputs.first, Node(inputs.first)));

		//Create right-hand node if it does not exist yet
		if (nodes.find(inputs.second) == nodes.end())
			nodes.insert(pair<string,Node>(inputs.second, Node(inputs.second)));

		//Make left-hand node parent of right-hand node
		Node *lnode = &nodes.at(inputs.first);
		Node *rnode = &nodes.at(inputs.second);
		lnode->append(rnode);

	}

	//Count orbits
	unsigned res = 0;
	Node *node;
	for (pair<string,Node> el : nodes)
	{
		node = &el.second;
		res += node->get_height();
	}
	cout << "Amount of direct and indirect orbits: " << res << endl;

	return 0;
}
