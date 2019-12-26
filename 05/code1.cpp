/*AoC day 5 part 1
Author(s)		: Lukas Mirow
Date of creation	: 2019-12-26
*/

#include <iostream>
#include "ici.hpp"
using namespace std;

int main(int argc, char **argv)
{
	ICI_TYPE test_prog[5] = {3,0,4,0,99};
	Intcode_interpreter ici(test_prog, 5);
	ici.run();
	cout << ici.dump_memory() << endl;
	return 0;
}
