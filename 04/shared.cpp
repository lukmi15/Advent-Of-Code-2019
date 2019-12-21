/*Shared code for AoC day 4
Author(s)		: Lukas Mirow
Date of creation	: 12/15/2019
*/

#define COUNTER_LENGTH 6

#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

string num2str(const unsigned num)
{
	stringstream ss;
	ss << num;
	return ss.str();
}

bool any_digit_decreases(const unsigned num)
{
	const char *s = num2str(num).c_str();
	unsigned i = 0;
	while (s[i+1] != '\0')
	{
		if (s[i+1] < s[i])
			return true;
		i++;
	}
	return false;
}

void print_counter(unsigned& counter)
{
	for (unsigned i=0; i<COUNTER_LENGTH; i++)
		cout << '\b';
	cout << setfill('0') << setw(COUNTER_LENGTH) << counter << flush;
}
