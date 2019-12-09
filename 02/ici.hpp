/*Intcode interpreter header
Author(s)		: Lukas Mirow
Date of creation	: 12/09/2019
*/

#ifndef INTCODE_INTERPRETER_HPP
#define INTCODE_INTERPRETER_HPP

#define STOP_CODE 99
#define ADD_CODE 1
#define MUL_CODE 2

#include <stdexcept>
#include <string>

typedef unsigned ICI_TYPE;

class Intcode_interpreter
{
	public:
		std::string dump_memory();
		Intcode_interpreter(ICI_TYPE *program, unsigned length) {load_program(program, length);}
		void step();
		void run();
		Intcode_interpreter() {delete memory;}
		ICI_TYPE get_memory_at(const unsigned address) {return memory[address];}

	private:
		unsigned memory_length;
		void load_program(const ICI_TYPE *program, const unsigned length);
		unsigned pc = 0;
		void add(ICI_TYPE a_address, ICI_TYPE b_address, unsigned target_address);
		void mul(ICI_TYPE a_address, ICI_TYPE b_address, unsigned target_address);
		ICI_TYPE *memory;
};

#endif //INTCODE_INTERPRETER_HPP
