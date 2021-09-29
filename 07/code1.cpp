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

//Perform one thruster run with set phase settings
ici_t fire_thrusters(ici_t *phase_settings, ici_t *program)
{
	ici_t amp_signal = INITIAL_AMP_SIGNAL;
	for (unsigned i = 0; i < AMPLIFIER_COUNT; i++)
	{
		Intcode_interpreter ici(program, sizeof(*program) / sizeof(ici_t));
		ici.input_queue.push(phase_settings[i]);
		ici.input_queue.push(amp_signal);
		ici.run();
		amp_signal = ici.last_outputs.back();
	}
	return amp_signal;
}

int main(int argc, char **argv)
{
	ici_t test1[17] = {3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0};
	ici_t phase_settings[AMPLIFIER_COUNT] = {0,1,2,3,4};
	ici_t curval, maxval = numeric_limits<int>::min();
	ici_t best_phase_settings[AMPLIFIER_COUNT] = {0};
	do
	{
		curval = fire_thrusters(phase_settings, test1);
		if (curval > maxval)
		{
			maxval = curval;
			memcpy(best_phase_settings, phase_settings, AMPLIFIER_COUNT);
		}
	}
	while (next_permutation(phase_settings, phase_settings + AMPLIFIER_COUNT));
	cout << "Best amplifier output: " << maxval << endl;
	cout << "Corresponding phase settings: ";
	for (unsigned i = 0; i < AMPLIFIER_COUNT; i++)
		cout << best_phase_settings[i] << ' ';
	cout << endl;
	return 0;
}
