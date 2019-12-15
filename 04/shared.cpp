/*Shared code for AoC day 4
Author(s)		: Lukas Mirow
Date of creation	: 12/15/2019
*/

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
		if (s[i] < s[i+1])
			return true;
		i++;
	}
	return false;
}

void increase_counter(unsigned& counter)
{
	counter++;
	for (unsigned i=0; i<6; i++)
		cout << '\b';
	cout << setfill('0') << setw(6) << counter << flush;
}
