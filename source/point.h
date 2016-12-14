#ifndef POINT_H
#define POINT_H

#include <iostream>

struct Point
{
public:
	Point(int initX, int initY)
	:	x{initX}, y{initY}
	{}

	Point& operator = (Point another)
	{
		x = another.x;
		y = another.y;
		return *this;
	}

	int x;
	int y;
};

bool operator == (const Point& first, const Point& second);

bool operator < (const Point& first, const Point& second);

const std::ostream& operator << (std::ostream& os, Point& point);

#endif