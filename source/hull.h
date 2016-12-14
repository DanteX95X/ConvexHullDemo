#ifndef HULL_H
#define HULL_H

#include "point.h"
#include <vector>
namespace ConvexHull
{
	int DistanceFromLine(Point start, Point end, Point point) ;
	std::vector<Point> FindHull(std::vector<Point> points, Point begin, Point end);
	std::vector<Point> Quickhull(std::vector<Point>& points);
}

#endif