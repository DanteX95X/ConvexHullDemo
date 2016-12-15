#include "point.h"

bool operator == (const Point& first, const Point& second)
{
	return first.x == second.x && first.y == second.y;
}

bool operator < (const Point& first, const Point& second)
{
	const int  temp = first.x - second.x;
	if(temp != 0)
	{
		return first.x < second.x;
	}
	return first.y < second.y;
}

const std::ostream& operator << (std::ostream& os, Point& point)
{
	os << point.x << " " << point.y << '\n';
	return os;
}