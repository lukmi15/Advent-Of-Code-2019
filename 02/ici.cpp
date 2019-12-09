/*Implementation for the Intcode interpreter for Aoc 2019 day 2
Author(s)		: Lukas Mirow
Date of creation	: 12/09/2019
*/

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
	switch (memory[pc])
	{
		case STOP_CODE:
			pc = -1;
			return;
		case ADD_CODE:
			add(memory[pc + 1], memory[pc + 2], memory[pc + 3]);
			break;
		case MUL_CODE:
			mul(memory[pc + 1], memory[pc + 2], memory[pc + 3]);
			break;
		default:
			stringstream ss;
			ss << "Invalid opcode `" << memory[pc] << "` at `" << pc << '`';
			throw runtime_error(ss.str());
	}
	pc += 4;
}

void Intcode_interpreter::run()
{
	while (pc < memory_length)
		step();
}

string Intcode_interpreter::dump_memory()
{
	stringstream ss;
	for (unsigned i=0; i<memory_length-1; i++)
		ss << memory[i] << ", ";
	ss << memory[memory_length - 1];
	return ss.str();
}

void Intcode_interpreter::add(ICI_TYPE a_address, ICI_TYPE b_address, unsigned target_address)
{
	memory[target_address] = memory[a_address] + memory[b_address];
}

void Intcode_interpreter::mul(ICI_TYPE a_address, ICI_TYPE b_address, unsigned target_address)
{
	memory[target_address] = memory[a_address] * memory[b_address];
}
