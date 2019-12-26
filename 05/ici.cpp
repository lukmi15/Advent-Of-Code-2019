/*Implementation for the Intcode interpreter for Aoc 2019 day 2
Author(s)		: Lukas Mirow
Date of creation	: 12/09/2019
*/

#define PARAMETER_MODE_ADDRESS 0
#define PARAMETER_MODE_IMMEDIATE 1

#include "ici.hpp"
#include <iostream>
#include <sstream>
#include <cstring>
using namespace std;

void Intcode_interpreter::load_program(const ICI_TYPE *program, const unsigned length)
{
	unsigned memory_size = length * sizeof(ICI_TYPE);
	memory_length = length;
	memory = new ICI_TYPE[memory_size];
	memcpy(memory, program, memory_size);
}

void Intcode_interpreter::step()
{
	unsigned parameter_count, *parameter_modes;
	switch (memory[pc] % 100)
	{
		case STOP_CODE:
			pc = -1;
			return;
		case ADD_CODE:
			parameter_count = 4; //TODO: How to properly add parameter mode support?
			/*ICI_TYPE params[parameter_count-1];
			for (unsigned i=0; i<parameter_count-1; i++)
				if (*/
			add(memory[pc + 1], memory[pc + 2], memory[pc + 3]);
			break;
		case MUL_CODE:
			mul(memory[pc + 1], memory[pc + 2], memory[pc + 3]);
			parameter_count = 4;
			break;
		case IN_CODE:
			in(memory[pc + 1]);
			parameter_count = 2;
			break;
		case OUT_CODE:
			out(memory[pc + 1]);
			parameter_count = 2;
			break;
		default:
			stringstream ss;
			ss << "Invalid opcode `" << memory[pc] << "` at `" << pc << '`';
			throw runtime_error(ss.str());
	}
	pc += parameter_count;
}

void Intcode_interpreter::run()
{
	while (pc < memory_length)
		step();
}

string Intcode_interpreter::dump_memory()
{
	stringstream ss;
	for (ICI_TYPE i=0; i<memory_length-1; i++)
		ss << memory[i] << ", ";
	ss << memory[memory_length - 1];
	return ss.str();
}

void Intcode_interpreter::add(const ICI_TYPE a_address, const ICI_TYPE b_address, const ICI_TYPE target_address)
{
	memory[target_address] = memory[a_address] + memory[b_address];
}

void Intcode_interpreter::mul(const ICI_TYPE a_address, const ICI_TYPE b_address, const ICI_TYPE target_address)
{
	memory[target_address] = memory[a_address] * memory[b_address];
}

void Intcode_interpreter::in(const ICI_TYPE address)
{
	cerr << "Expecting input for address '" << address << "': " << flush;
	cin >> memory[address];
};

void Intcode_interpreter::out(const ICI_TYPE address)
{
	cout << "Output from address: '" << address << "': " << memory[address] << endl;
};
