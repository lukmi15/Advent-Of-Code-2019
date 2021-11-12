/*AoC day 7 part 1
Author(s)		: Lukas Mirow
Date of creation	: 9/29/2021
*/

#include <iostream>
#include "ici.hpp"
#include <algorithm>
#include <limits>
#include <cstring>
using namespace std;

constexpr ici_t INITIAL_AMP_SIGNAL = 0;
constexpr size_t AMPLIFIER_COUNT = 5;

//Perform one thruster run with phase settings and program
ici_t fire_thrusters(ici_t *phase_settings, ici_t *program, const size_t prog_length)
{
	ici_t amp_signal = INITIAL_AMP_SIGNAL;
	for (unsigned i = 0; i < AMPLIFIER_COUNT; i++)
	{
		//Load program
		Intcode_interpreter ici(program, prog_length);

		//Push parameters
		ici.input_queue.push(phase_settings[i]);
		ici.input_queue.push(amp_signal);

		//Run program
		ici.run();

		//Get output
		amp_signal = ici.last_outputs.back();
	}
	return amp_signal;
}

//ici_t simulate_amplifier(ici_t phase_setting, input_value, ici_t *prog)

int main(int argc, char **argv)
{
	constexpr size_t test1_len = 17;
	ici_t test1[test1_len] = {3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0};
	constexpr size_t test2_len = 25;
	ici_t test2[test2_len] = {3,23,3,24,1002,24,10,24,1002,23,-1,23,101,5,23,23,1,24,23,23,4,23,99,0,0};
	constexpr size_t test3_len = 34;
	ici_t test3[test3_len] = {3,31,3,32,1002,32,10,32,1001,31,-2,31,1007,31,0,33,1002,33,7,33,1,33,31,31,1,32,31,31,4,31,99,0,0,0};
	constexpr size_t real_prog_len = 523;
	ici_t real_prog[real_prog_len] = {3,8,1001,8,10,8,105,1,0,0,21,38,55,68,93,118,199,280,361,442,99999,3,9,1002,9,2,9,101,5,9,9,102,4,9,9,4,9,99,3,9,101,3,9,9,1002,9,3,9,1001,9,4,9,4,9,99,3,9,101,4,9,9,102,3,9,9,4,9,99,3,9,102,2,9,9,101,4,9,9,102,2,9,9,1001,9,4,9,102,4,9,9,4,9,99,3,9,1002,9,2,9,1001,9,2,9,1002,9,5,9,1001,9,2,9,1002,9,4,9,4,9,99,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,99,3,9,1001,9,1,9,4,9,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,2,9,4,9,99,3,9,1001,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,1,9,4,9,99,3,9,102,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,2,9,9,4,9,99};
	ici_t phase_settings[AMPLIFIER_COUNT] = {0,1,2,3,4};
	ici_t curval, maxval = numeric_limits<int>::min();
	ici_t best_phase_settings[AMPLIFIER_COUNT] = {0};
	do
	{
		curval = fire_thrusters(phase_settings, real_prog, real_prog_len);
		cout << "Output for phase setting ";
		for (unsigned i = 0; i < AMPLIFIER_COUNT; i++)
			cout << phase_settings[i];
		cout << " was " << curval << endl;
		if (curval > maxval)
		{
			maxval = curval;
			memcpy(best_phase_settings, phase_settings, AMPLIFIER_COUNT * sizeof(ici_t));
		}
	}
	while (next_permutation(phase_settings, phase_settings + AMPLIFIER_COUNT));
	cout << "Best amplifier output: " << maxval << " with phase settings ";
	for (unsigned i = 0; i < AMPLIFIER_COUNT; i++)
		cout << best_phase_settings[i];
	cout << endl;
	return 0;
}
