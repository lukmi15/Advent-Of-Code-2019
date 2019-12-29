/*AoC 2019 day 5 part 2
Author(s)		: Lukas Mirow
Date of creation	: 2019/12/29
*/

#include <iostream>
#include "ici.hpp"
using namespace std;

int main(int argc, char **argv)
{
	ici_t position_mode_equal_test[] = {3,9,8,9,10,9,4,9,99,-1,8};
	ici_t position_mode_less_test[] = {3,9,7,9,10,9,4,9,99,-1,8};
	ici_t immediate_mode_equal_test[] = {3,3,1108,-1,8,3,4,3,99};
	ici_t immediate_mode_less_test[] = {3,3,1107,-1,8,3,4,3,99};
	ici_t position_mode_jump_test[] = {3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9};
	ici_t immediate_mode_jump_test[] = {3,3,1105,-1,9,1101,0,0,12,4,12,99,1};
	ici_t less_equal_greater_test[] = {3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,}; //FIXME
	Intcode_interpreter ici(less_equal_greater_test, sizeof(less_equal_greater_test) / sizeof(ici_t));
	ici.run();
	cout << ici.dump_memory() << endl;
	return 0;
}
