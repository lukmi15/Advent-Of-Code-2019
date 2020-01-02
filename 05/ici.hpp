/*Intcode interpreter header
Author(s)		: Lukas Mirow
Date of creation	: 12/09/2019
*/

#ifndef INTCODE_INTERPRETER_HPP
#define INTCODE_INTERPRETER_HPP

#define PARAMETER_MODE_ADDRESS 0
#define PARAMETER_MODE_IMMEDIATE 1

#define STOP_CODE 99
#define ADD_CODE 1
#define MUL_CODE 2
#define IN_CODE 3
#define OUT_CODE 4
#define JUMP_IF_TRUE_CODE 5
#define JUMP_IF_FALSE_CODE 6
#define LESS_THAN_CODE 7
#define EQUAL_TO_CODE 8

#include <stdexcept>
#include <string>
#include <vector>
#include <functional>

typedef int ici_t;

typedef unsigned parameter_mode_t;

class Intcode_interpreter
{
	public:
		std::string dump_memory();
		Intcode_interpreter(ici_t *program, unsigned length) {load_program(program, length);}
		void step();
		void run();
		~Intcode_interpreter() {delete memory;}
		ici_t get_memory_at(const ici_t address) {return memory[address];}

	private:
		unsigned memory_length;
		void load_program(const ici_t *program, const unsigned length);
		unsigned pc = 0;
		void add(const std::vector<ici_t>& params);
		void mul(const std::vector<ici_t>& params);
		void in(const std::vector<ici_t>& params);
		void out(const std::vector<ici_t>& params);
		ici_t *memory;
		std::vector<parameter_mode_t> get_parameter_modes(const unsigned parameter_count, const ici_t instruction);
		ici_t parameter_to_value(const ici_t param, const parameter_mode_t parameter_mode);
		void jump_if_true(const std::vector<ici_t>& params);
		void jump_if_false(const std::vector<ici_t>& params);
		void less_than(const std::vector<ici_t>& params);
		void equal_to(const std::vector<ici_t>& params);
		void validate_parameter_modes_for_writing_instructions(const std::vector<parameter_mode_t>& pms);
		void execute_writing_operation(const std::function<void(const std::vector<ici_t>&)> op, const unsigned parameter_count);
		void execute_non_writing_operation(const std::function<void(const std::vector<ici_t>&)> op, const unsigned parameter_count);
};

#endif //INTCODE_INTERPRETER_HPP
