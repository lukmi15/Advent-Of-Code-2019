/*Implementation for the Intcode interpreter for Aoc 2019 day 2
Author(s)		: Lukas Mirow
Date of creation	: 12/09/2019
*/

#include "ici.hpp"
#include <iostream>
#include <sstream>
#include <cstring>
#include <cmath>
#include <stdexcept>
#include <queue>
using namespace std;

void Intcode_interpreter::load_program(const ici_t *program, const unsigned length)
{
	unsigned memory_size = length * sizeof(ici_t);
	memory_length = length;
	memory = new ici_t[memory_size];
	memcpy(memory, program, memory_size);
}

void Intcode_interpreter::validate_parameter_modes_for_writing_instructions(const vector<parameter_mode_t>& pms)
{
	if (pms.back() == PARAMETER_MODE_IMMEDIATE)
	{
		stringstream ss;
		ss << "The address being written to can never be in immediate mode";
		throw invalid_argument(ss.str());
	}
}

vector<parameter_mode_t> Intcode_interpreter::get_parameter_modes(const unsigned parameter_count, const ici_t instruction)
{
	vector<parameter_mode_t> pms;
	parameter_mode_t parameter_mode;
	for (unsigned current_parameter_mask = 100; current_parameter_mask < (unsigned)pow(10, parameter_count + 2); current_parameter_mask *= 10)
	{
		parameter_mode = (instruction % (current_parameter_mask * 10)) / current_parameter_mask;
		if (parameter_mode < PARAMETER_MODE_ADDRESS or parameter_mode > PARAMETER_MODE_IMMEDIATE)
		{
			stringstream ss;
			ss << "Invalid parameter mode `" << parameter_mode << '`';
			throw invalid_argument(ss.str());
		}
		else
			pms.push_back(parameter_mode);
	}
	return pms;
}

void Intcode_interpreter::step()
{
	unsigned parameter_count;
	vector<unsigned> parameter_modes;
	switch (memory[pc] % 100)
	{ //TODO: Break the stuff in every case block down into a function of common operations
		case STOP_CODE:
			pc = -1;
			return;
		case ADD_CODE:
			parameter_count = 4;
			parameter_modes = get_parameter_modes(parameter_count, memory[pc]);
			validate_parameter_modes_for_writing_instructions(parameter_modes);
			add(memory[pc + 1], memory[pc + 2], memory[pc + 3], parameter_modes);
			break;
		case MUL_CODE:
			parameter_count = 4;
			parameter_modes = get_parameter_modes(parameter_count, memory[pc]);
			validate_parameter_modes_for_writing_instructions(parameter_modes);
			mul(memory[pc + 1], memory[pc + 2], memory[pc + 3], parameter_modes);
			break;
		case IN_CODE:
			in(memory[pc + 1]);
			parameter_count = 2;
			break;
		case OUT_CODE:
			out(memory[pc + 1]);
			parameter_count = 2;
			break;
		case JUMP_IF_TRUE_CODE:
			parameter_count = 3;
			parameter_modes = get_parameter_modes(parameter_count, memory[pc]);
			jump_if_true(memory[pc + 1], memory[pc + 2], parameter_modes, parameter_count);
			break;
		case JUMP_IF_FALSE_CODE:
			parameter_count = 3;
			parameter_modes = get_parameter_modes(parameter_count, memory[pc]);
			jump_if_false(memory[pc + 1], memory[pc + 2], parameter_modes, parameter_count);
			break;
		case LESS_THAN_CODE:
			parameter_count = 4;
			parameter_modes = get_parameter_modes(parameter_count, memory[pc]);
			validate_parameter_modes_for_writing_instructions(parameter_modes);
			less_than(memory[pc + 1], memory[pc + 2], memory[pc + 3], parameter_modes);
			break;
		case EQUAL_TO_CODE:
			parameter_count = 4;
			parameter_modes = get_parameter_modes(parameter_count, memory[pc]);
			validate_parameter_modes_for_writing_instructions(parameter_modes);
			equal_to(memory[pc + 1], memory[pc + 2], memory[pc + 3], parameter_modes);
			break;
		default:
			stringstream ss;
			ss << "Invalid opcode `" << memory[pc] << "` at address `" << pc << '`';
			ss << "\nMemory dump:\n" << dump_memory();
			throw invalid_argument(ss.str());
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
	for (ici_t i=0; i<(int)memory_length-1; i++)
		ss << memory[i] << ", ";
	ss << memory[memory_length - 1];
	return ss.str();
}

ici_t Intcode_interpreter::parameter_to_value(const ici_t param, const parameter_mode_t parameter_mode)
{
	if (parameter_mode == PARAMETER_MODE_IMMEDIATE)
		return param;
	else
		return memory[param];
}

void Intcode_interpreter::add(const ici_t a_param, const ici_t b_param, const ici_t target_address, const vector<parameter_mode_t> parameter_modes)
{
	ici_t a_value, b_value;
	a_value = parameter_to_value(a_param, parameter_modes[0]);
	b_value = parameter_to_value(b_param, parameter_modes[1]);
	memory[target_address] = a_value + b_value;
}

void Intcode_interpreter::mul(const ici_t a_param, const ici_t b_param, const ici_t target_address, const vector<parameter_mode_t> parameter_modes)
{
	ici_t a_value, b_value;
	a_value = parameter_to_value(a_param, parameter_modes[0]);
	b_value = parameter_to_value(b_param, parameter_modes[1]);
	memory[target_address] = a_value * b_value;
}

void Intcode_interpreter::in(const ici_t address)
{
	if (input_queue.size() > 0)
	{
		memory[address] = input_queue.front();
		input_queue.pop();
		return;
	}
	cerr << "Expecting input for address '" << address << "': " << flush;
	cin >> memory[address];
}

void Intcode_interpreter::out(const ici_t address)
{
	//cout << "Output from address: '" << address << "': " << memory[address] << endl; //FIXME: This is displayed after input of TEST
	last_outputs.push(memory[address]);
}

void Intcode_interpreter::jump_if_true(const ici_t condition, const ici_t target_param, const vector<parameter_mode_t> parameter_modes, const unsigned parameter_count)
{
	ici_t condition_value = parameter_to_value(condition, parameter_modes[0]);
	ici_t target_address = parameter_to_value(target_param, parameter_modes[1]);
	if (condition_value)
		pc = target_address - parameter_count;
}

void Intcode_interpreter::jump_if_false(const ici_t condition, const ici_t target_param, const vector<parameter_mode_t> parameter_modes, const unsigned parameter_count)
{
	ici_t condition_value = parameter_to_value(condition, parameter_modes[0]);
	ici_t target_address = parameter_to_value(target_param, parameter_modes[1]);
	if (!condition_value)
		pc = target_address - parameter_count;
}

void Intcode_interpreter::less_than(const ici_t a_param, const ici_t b_param, const ici_t target_address, const std::vector<parameter_mode_t> parameter_modes)
{
	ici_t a_value, b_value;
	a_value = parameter_to_value(a_param, parameter_modes[0]);
	b_value = parameter_to_value(b_param, parameter_modes[1]);
	memory[target_address] = a_value < b_value;
}

void Intcode_interpreter::equal_to(const ici_t a_param, const ici_t b_param, const ici_t target_address, const std::vector<parameter_mode_t> parameter_modes)
{
	ici_t a_value, b_value;
	a_value = parameter_to_value(a_param, parameter_modes[0]);
	b_value = parameter_to_value(b_param, parameter_modes[1]);
	memory[target_address] = a_value == b_value;
}
