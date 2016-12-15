#include "hull.h"
#include <climits>

//negative - clockwise, positive - counterclockwise
int ConvexHull::DistanceFromLine(Point start, Point end, Point point) 
{
	int a = end.y - start.y;
	int b = start.x - end.x;
	int c = start.y * end.x - start.x * end.y;
	return -(a * point.x + b * point.y + c);
}
	


std::vector<Point> ConvexHull::FindHull(std::vector<Point> points, Point begin, Point end)
{
	std::vector<Point> partOfHull;
	
	if(points.size() == 0)
		return partOfHull;
	
	
	int maxDistance = INT_MIN;
	Point maxPoint = points[0];
	for(auto point : points)
	{
		double distance = DistanceFromLine(begin, end, point);
		if(distance > maxDistance)
		{
			maxDistance = distance;
			maxPoint = point;
		}
	}

	std::vector<Point> firstSet, secondSet;
	for(auto point : points)
	{
		int distance = DistanceFromLine(begin, maxPoint, point);
		if(distance > 0)
			firstSet.push_back(point);
		
		distance = DistanceFromLine(maxPoint, end, point);
		if(distance > 0)
			secondSet.push_back(point);
	}
	
	std::vector<Point> leftPart = FindHull(firstSet, begin, maxPoint);
	partOfHull.insert(partOfHull.end(), leftPart.begin(), leftPart.end());
	partOfHull.push_back(maxPoint);
	std::vector<Point> rightPart = FindHull(secondSet, maxPoint, end);
	partOfHull.insert(partOfHull.end(), rightPart.begin(), rightPart.end());
	
	return partOfHull;
}

std::vector<Point> ConvexHull::Quickhull(std::vector<Point>& points)
{
	std::vector<Point> hull;
	
	Point minPoint(INT_MAX, INT_MAX);
	Point maxPoint(INT_MIN, INT_MIN);
	
	for(std::size_t i = 0; i < points.size(); ++i)
	{
		if(points[i] < minPoint)
			minPoint = points[i];
		if(maxPoint < points[i])
			maxPoint = points[i];
	}
	
	
	std::vector<Point> above;
	std::vector<Point> below;
	for(auto point : points)
	{
		
		int distance = DistanceFromLine(minPoint, maxPoint, point);
		if(distance > 0)
			above.push_back(point);
			
		distance = DistanceFromLine(maxPoint, minPoint, point);
		if(distance > 0)
			below.push_back(point);
	}
	
	hull.push_back(minPoint);
	std::vector<Point> leftPart = FindHull(above, minPoint, maxPoint);
	hull.insert(hull.end(), leftPart.begin(), leftPart.end());
	hull.push_back(maxPoint);
	std::vector<Point> rightPart = FindHull(below, maxPoint, minPoint);
	hull.insert(hull.end(), rightPart.begin(), rightPart.end());
	
	std::cout << hull.size() << '\n';
	for(auto point : hull)
		std::cout << point;
		
	return hull;
}