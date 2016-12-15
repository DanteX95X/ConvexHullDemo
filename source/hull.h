#ifndef HULL_H
#define HULL_H

#include "point.h"
#include <vector>
namespace ConvexHull
{
	int DistanceFromLine(Point start, Point end, Point point) ;
	std::vector<Point> FindHull(const std::vector<Point>& points, Point begin, Point end);
	std::vector<Point> Quickhull(const std::vector<Point>& points);
	
	double CrossProduct(Point origin, Point first, Point second);
	std::vector<Point> MonotoneChain(std::vector<Point>& points);
	
	std::vector<Point> GiftWrapping(const std::vector<Point>& points);
}

#endif