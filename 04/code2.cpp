/*AoC 2019 day 4 part 2
Author(s)		: Lukas Mirow
Date of creation	: 12/15/2019
*/

#include <iostream>
#include <iomanip>
#include "shared.cpp"
using namespace std;

bool next_char_is_equal(const char *str, const unsigned i)
{
	return str[i] == str[i+1];
}

bool next_next_char_is_equal(const char *str, const unsigned i)
{
	return next_char_is_equal(str, i+1);
}

bool prev_char_is_equal(const char *str, const unsigned i)
{
	return next_char_is_equal(str, i-1);
}

bool has_adjacent_twin(const unsigned num)
{
	unsigned i = 1;
	const char *s = num2str(num).c_str();
	while (s[i+1] != '\0')
	{
		if (next_char_is_equal(s, i) and not next_next_char_is_equal(s, i) and not prev_char_is_equal(s, i))
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
	// cout << is_valid(112233) << endl;
	// cout << is_valid(123444) << endl;
	// cout << is_valid(111122) << endl;
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
