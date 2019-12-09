/*AoC day 2 part 2
Author(s)		: Lukas Mirow
Date of creation	: 12/09/2019
*/

#define DESIRED_OUTPUT 19690720
#include "ici.hpp"
#include <iostream>
using namespace std;

bool try_input_for_gravity_assist_prog(ICI_TYPE noun, ICI_TYPE verb)
{
	ICI_TYPE gravity_assist_program[173] = {1,noun ,verb ,3,1,1,2,3,1,3,4,3,1,5,0,3,2,13,1,19,1,6,19,23,2,6,23,27,1,5,27,31,2,31,9,35,1,35,5,39,1,39,5,43,1,43,10,47,2,6,47,51,1,51,5,55,2,55,6,59,1,5,59,63,2,63,6,67,1,5,67,71,1,71,6,75,2,75,10,79,1,79,5,83,2,83,6,87,1,87,5,91,2,9,91,95,1,95,6,99,2,9,99,103,2,9,103,107,1,5,107,111,1,111,5,115,1,115,13,119,1,13,119,123,2,6,123,127,1,5,127,131,1,9,131,135,1,135,9,139,2,139,6,143,1,143,5,147,2,147,6,151,1,5,151,155,2,6,155,159,1,159,2,163,1,9,163,0,99,2,0,14,0};
	Intcode_interpreter ici(gravity_assist_program, 173);
	ici.run();
	return (ici.get_memory_at(0) == DESIRED_OUTPUT);
}

unsigned guess_input_for_gravity_assist_prog()
{
	for (ICI_TYPE noun=0; noun<100; noun++)
		for (ICI_TYPE verb=0; verb<100; verb++)
			if (try_input_for_gravity_assist_prog(noun, verb))
				return noun * 100 + verb;
	return -1;
}

int main(int argc, char **argv)
{
	cout << guess_input_for_gravity_assist_prog() << endl;
	return 0;
}
