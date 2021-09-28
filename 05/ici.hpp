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
		void add(const ici_t a_param, const ici_t b_param, const ici_t target_address, std::vector<parameter_mode_t> parameter_modes);
		void mul(const ici_t a_param, const ici_t b_param, const ici_t target_address, std::vector<parameter_mode_t> parameter_modes);
		void in(const ici_t address);
		void out(const ici_t _address);
		ici_t *memory;
		std::vector<parameter_mode_t> get_parameter_modes(const unsigned parameter_count, const ici_t instruction);
		ici_t parameter_to_value(const ici_t param, const parameter_mode_t parameter_mode);
		void jump_if_true(const ici_t condition, const ici_t target_param, const std::vector<parameter_mode_t> parameter_modes, const unsigned parameter_count);
		void jump_if_false(const ici_t condition, const ici_t target_param, const std::vector<parameter_mode_t> parameter_modes, const unsigned parameter_count);
		void less_than(const ici_t a_param, const ici_t b_param, const ici_t target_address, const std::vector<parameter_mode_t> parameter_modes);
		void equal_to(const ici_t a_param, const ici_t b_param, const ici_t target_address, const std::vector<parameter_mode_t> parameter_modes);
		void validate_parameter_modes_for_writing_instructions(const std::vector<parameter_mode_t>& pms);
};

#endif //INTCODE_INTERPRETER_HPP
