/*AoC 2019 day 4 part 1
Author(s)		: Lukas Mirow
Date of creation	: 12/15/2019
*/

#include <iostream>
#include <iomanip>
#include "shared.cpp"
using namespace std;

bool has_adjacent_twin(const unsigned num)
{
	unsigned i = 0;
	const char *s = num2str(num).c_str();
	while (s[i] != '\0')
	{
		if (s[i] == s[i+1])
			return true;
		i++;
	}
	return false;
}

bool is_valid(unsigned num)
{
	if (num < 234208 or num > 765869)
		return false;
	if (not has_adjacent_twin(num))
		return false;
	if (any_digit_decreases(num))
		return false;
	return true;
}

int main(int argc, char **argv)
{
	unsigned start = 234208, stop = 765869, counter = 0;
	print_counter(counter);
	for (unsigned i = start; i <= stop; i++)
		if (is_valid(i))
		{
			counter++;
			print_counter(counter);
		}
	cout << endl;
	return 0;
}
