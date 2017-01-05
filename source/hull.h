#ifndef HULL_H
#define HULL_H

#include "point.h"
#include <vector>
namespace ConvexHull
{
	extern std::string imagePath;
	extern unsigned int alphaThreshold;
	
	std::vector<Point> CalculateConvexHull(std::vector<Point>& points);
}

#endif