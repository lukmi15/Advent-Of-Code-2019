/*AoC 2019 day 4 part 2
Author(s)		: Lukas Mirow
Date of creation	: 12/15/2019
*/

#include <iostream>
#include <iomanip>
#include "shared.cpp"
using namespace std;

bool is_next_char_equal(const char *str, const unsigned i)
{
	return str[i] == str[i+1];
}

bool is_next_next_char_equal(const char *str, const unsigned i)
{
	return is_next_char_equal(str, i+1);
}

bool is_prev_char_equal(const char *str, const unsigned i)
{
	return is_next_char_equal(str, i-1);
}

bool check_twin_validity(const unsigned num)
{
	const char *s = num2str(num).c_str();
	for (unsigned i=0; s[i+1] != '\0'; i++)
		if (is_next_char_equal(s, i) and not is_next_next_char_equal(s, i))
		{
			if (i > 0 and is_prev_char_equal(s, i))
				continue;
			return true;
		}
	return false;
}

bool is_in_range(const unsigned num)
{
	return 234208 <= num and num <= 765869;
}

bool is_valid(unsigned num)
{
	return is_in_range(num) and check_twin_validity(num) and not any_digit_decreases(num);
}

int main(int argc, char **argv)
{
	// cout << "112233: " << is_valid(112233) << endl;
	// cout << "123444: " << is_valid(123444) << endl;
	// cout << "111122: " << is_valid(111122) << endl;
	// cout << "224522: " << is_valid(224522) << endl;
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
