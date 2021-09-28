/*Tree for AoC 2019
Author(s)		: Lukas Mirow
Date of creation	: 9/28/2021
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Node
{

	const string name;
	Node *parent;
	vector<Node*> children; //TODO: Make this a map

	Node(const string name, Node *parent = NULL) : name(name), parent(parent) {};

	unsigned get_height() const
	{
		unsigned ret = 0;
		const Node *current_node = this;
		while (current_node->parent != NULL)
		{
			ret++;
			current_node = current_node->parent;
		}
		return ret;
	}

	void append(Node *n)
	{
		n->parent = this;
		children.push_back(n);
	}

	void print_tree(const unsigned indent_level = 0) const
	{

		//If we don't start at the root, find it and start there
		if (parent != NULL and indent_level == 0)
		{
			const Node *current_node = this;
			while (current_node->parent != NULL)
				current_node = current_node->parent;
			current_node->print_tree();
			return;
		}

		//Recursively print all nodes in a breadth-first manner
		for (unsigned i = 0; i < indent_level; i++)
			cout << '\t';
		cout << '(' << name << ')' << endl;
		for (Node *child : children)
			child->print_tree(indent_level + 1);
	}

};

#ifdef DEBUG
int main(int argc, char **argv)
{
	Node root = Node("I am root");
	Node c1 = Node("I am a child");
	Node c2 = Node("I am root jr.");
	Node c3 = Node("I am a sub-child");
	root.append(&c1);
	root.append(&c2);
	c1.append(&c3);
	c3.print_tree();
	return 0;
}
#endif //DEBUG
