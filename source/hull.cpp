#include "hull.h"
#include <climits>
#include <algorithm>

unsigned int ConvexHull::alphaThreshold = 0;
std::string ConvexHull::imagePath = "weirdFace.png";

//Samples of input sets for convex hull problem
//std::vector<Point> input = { {-10,10}, {-7,3}, {-10,-10}, {-1,9}, {-1,0}, {-2,-3}, {6,4}, {5,-3}, {10,10}, {10,-10}};
	//output = { {-10,-10}, {-10,10} , {10, 10}, {10, -10} }
//std::vector<Point> input = {{2, 1}, {2, 1}, {2, 1}, {3, 1}, {3, 1}, {3, 2}, {4, 3}, {5, 2}, {5, 1}, {4, 0}, {2, 0}, {2, 1}};
	//output = { {2, 0}, {2, 1}, {4, 3}, {5, 2}, {5, 1}, {4, 0} }
//std::vector <Point> input = {{20, 13}, {24, 17}, {28, 18}, {34, 12}, {37, 16}, {34, 20}, {41, 30}, {53, 26}, {54, 12}, {49, 8}, {29, 7}, {20, 13}};
	//output = { {20, 13}, {24, 17}, {41, 30}, {53, 26}, {54, 12}, {49, 8}, {29, 7} }

std::vector<Point> ConvexHull::CalculateConvexHull(std::vector<Point>& points)
{
	return std::vector<Point>();
}