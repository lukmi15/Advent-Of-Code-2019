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
#include <vector>
#include <algorithm>
using namespace std;

#define DEBUG

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

vector<Node*> get_reverse_orbit_list(Node *node)
{
	vector<Node*> res;
	while (node->parent != NULL)
	{
		res.push_back(node);
		node = node->parent;
	}
	return res;
}

int main(int argc, char **argv)
{

#ifndef DEBUG
	//Open file
	ifstream f;
	f.open("in1.txt");
	if (!f.is_open())
		err("Error opening file");
#endif //DEBUG

	//Create tree and node table from file
	map<string,Node*> nodes;
#ifdef DEBUG
	for (string line : {"COM)B", "B)C" ,"C)D" ,"D)E" ,"E)F" ,"B)G" ,"G)H" ,"D)I" ,"E)J" ,"J)K" ,"K)L" ,"K)YOU" ,"I)SAN"})
#else //DEBUG
	string line;
	while (getline(f, line))
#endif //DEBUG
	{

		//Pre-process input
		pair<string,string> inputs = split_input(line);

		//Create left-hand node if it does not exist yet
		if (nodes.find(inputs.first) == nodes.end())
			nodes.insert(pair<string,Node*>(inputs.first, new Node(inputs.first)));

		//Create right-hand node if it does not exist yet
		if (nodes.find(inputs.second) == nodes.end())
			nodes.insert(pair<string,Node*>(inputs.second, new Node(inputs.second)));

		//Make left-hand node parent of right-hand node
		Node *lnode = nodes.at(inputs.first);
		Node *rnode = nodes.at(inputs.second);
		lnode->append(rnode);

	}

	//Create list of orbits back to center of mass (COM)
	Node *you = nodes["YOU"];
	Node *san = nodes["SAN"];
	vector<Node*> you_orbits = get_reverse_orbit_list(you);
	vector<Node*> san_orbits = get_reverse_orbit_list(san);
	Node *last_common_node = NULL;

	//Find last common node
	size_t index_you, index_san;
	for (size_t i = 0;; i++)
	{
		index_you = you_orbits.size() - i;
		index_san = san_orbits.size() - i;
		if (index_you < 0 or index_san < 0)
			err("Index ran out of bounds trying to find the last common node");
		if (you_orbits[index_you] == san_orbits[index_san])
			last_common_node = you_orbits[index_you];
		else
			break;
	}

	//Calculate hops from common node to YOU's and SAN's orbit and add them up
	cout << "Distance of YOU to SAN: " << you->get_height() + san->get_height() - 2 * last_common_node->get_height() - 2 << endl;

	//Clean up
	for (pair<string,Node*> node_pair : nodes)
		delete node_pair.second;
#ifndef DEBUG
	f.close();
#endif //DEBUG

	return 0;
}
