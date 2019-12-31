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

ici_t Intcode_interpreter::parameter_to_value(const ici_t param, const parameter_mode_t parameter_mode)
{
	if (parameter_mode == PARAMETER_MODE_IMMEDIATE)
		return param;
	else
		return memory[param];
}

void Intcode_interpreter::execute_writing_operation(const function<void(const vector<const ici_t>&) op, const unsigned parameter_count)
{
	const vector<const ici_t> parameters;
	vector<parameter_mode_t> parameter_modes = get_parameter_modes(parameter_count, memory[pc]);
	validate_parameter_modes_for_writing_instructions(parameter_modes);
	for (unsigned i = 1; i < parameter_count; i++)
		parameters.push_back(parameter_to_value(memory[pc + i], parameter_modes[i - 1]));
	op(parameters);
}

void Intcode_interpreter::execute_non_writing_operation(const function<void(const vector<const ici_t>&) op, const unsigned parameter_count)
{
	const vector<const ici_t> parameters;
	vector<parameter_mode_t> parameter_modes = get_parameter_modes(parameter_count, memory[pc]);
	for (unsigned i = 1; i < parameter_count; i++)
		parameters.push_back(parameter_to_value(memory[pc + i], parameter_modes[i - 1]));
	op(parameters);
}

void Intcode_interpreter::step()
{
	unsigned parameter_count;
	vector<unsigned> parameter_modes;
	switch (memory[pc] % 100)
	{
		case STOP_CODE:
			pc = -1;
			return;
		case ADD_CODE:
			parameter_count = 4;
			execute_writing_operation(add, parameter_count);
			break;
		case MUL_CODE:
			parameter_count = 4;
			execute_writing_operation(mul, parameter_count);
			break;
		case IN_CODE:
			parameter_count = 2;
			execute_writing_operation(in, parameter_count);
			break;
		case OUT_CODE:
			parameter_count = 2;
			execute_non_writing_operation(in, parameter_count);
			break;
		case JUMP_IF_TRUE_CODE:
			parameter_count = 3;
			execute_non_writing_operation(jump_if_true, parameter_count);
			break;
		case JUMP_IF_FALSE_CODE:
			parameter_count = 3;
			execute_non_writing_operation(jump_if_false, parameter_count);
			break;
		case LESS_THAN_CODE:
			parameter_count = 4;
			execute_writing_operation(less_than, parameter_count);
			break;
		case EQUAL_TO_CODE:
			parameter_count = 4;
			execute_writing_operation(equal_to, parameter_count);
			break;
		default:
			stringstream ss;
			ss << "Invalid opcode `" << memory[pc] << "` at address `" << pc << '`';
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

void Intcode_interpreter::add(const ici_t *params)
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
	cerr << "Expecting input for address '" << address << "': " << flush;
	cin >> memory[address];
}

void Intcode_interpreter::out(const ici_t address)
{
	cout << "Output from address: '" << address << "': " << memory[address] << endl; //FIXME: This is displayed after input of TEST
}

void Intcode_interpreter::jump_if_true(const ici_t condition, const ici_t target_address, const vector<parameter_mode_t> parameter_modes, const unsigned parameter_count)
{
	ici_t condition_value = parameter_to_value(condition, parameter_modes[0]);
	if (condition_value)
		pc = target_address - parameter_count;
}

void Intcode_interpreter::jump_if_false(const ici_t condition, const ici_t target_address, const vector<parameter_mode_t> parameter_modes, const unsigned parameter_count)
{
	ici_t condition_value = parameter_to_value(condition, parameter_modes[0]);
	cout << "pc: " << pc << endl;
	if (!condition_value)
	{
		cout << "condition met" << endl;
		pc = memory[target_address] - parameter_count;
	}
	cout << "pc: " << pc << endl;
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
