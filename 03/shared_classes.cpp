/*AoC classes for day 3
Author(s)		: Lukas Mirow
Date of creation	: 12/09/2019
*/

#ifndef AOC_2019_DAY3_SHARED_CLASSES
#define AOC_2019_DAY3_SHARED_CLASSES

#define VAL_TYPE int
#define UNSIGNED_VAL_TYPE unsigned

#include <vector>
#include <iostream>
using namespace std;

struct Point
{
	Point(const VAL_TYPE h, const VAL_TYPE v) : horizontal(h), vertical(v) {}
	VAL_TYPE horizontal, vertical;
};

class Wire
{
	public:
		Wire& up(const VAL_TYPE dist);
		Wire& right(const VAL_TYPE dist);
		Wire& down(const VAL_TYPE dist);
		Wire& left(const VAL_TYPE dist);
		const vector<Point>& get_points() {return points;}
		Wire() {points.push_back(Point(0,0));}

	private:
		vector<Point> points;
};

Wire& Wire::up(const VAL_TYPE dist)
{
	Point current_pt = points.back();
	cerr << 'U' << dist << endl;
	for (VAL_TYPE v=current_pt.vertical+1; v<=current_pt.vertical+dist; v++)
		points.push_back(Point(current_pt.horizontal, v));
	return *this;
}

Wire& Wire::right(const VAL_TYPE dist)
{
	Point current_pt = points.back();
	cerr << 'R' << dist << endl;
	for (VAL_TYPE h=current_pt.horizontal+1; h<=current_pt.horizontal+dist; h++)
		points.push_back(Point(h, current_pt.vertical));
	return *this;
}

Wire& Wire::down(const VAL_TYPE dist)
{
	Point current_pt = points.back();
	cerr << 'D' << dist << endl;
	for (VAL_TYPE v=current_pt.vertical-1; v>=current_pt.vertical-dist; v--)
		points.push_back(Point(current_pt.horizontal, v));
	return *this;
}

Wire& Wire::left(const VAL_TYPE dist)
{
	Point current_pt = points.back();
	cerr << 'L' << dist << endl;
	for (VAL_TYPE h=current_pt.horizontal-1; h>=current_pt.horizontal-dist; h--)
		points.push_back(Point(h, current_pt.vertical));
	return *this;
}

#endif //AOC_2019_DAY3_SHARED_CLASSES
