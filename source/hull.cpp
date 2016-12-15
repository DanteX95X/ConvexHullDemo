#include "hull.h"
#include <climits>
#include <algorithm>

//positive - clockwise, negative - counterclockwise
int ConvexHull::DistanceFromLine(Point start, Point end, Point point) 
{
	int a = end.y - start.y;
	int b = start.x - end.x;
	int c = start.y * end.x - start.x * end.y;
	return -(a * point.x + b * point.y + c);
}
	
//negative - clockwise, positive - counterclockwise, zero - collinear
double ConvexHull::CrossProduct(Point origin, Point first, Point second)
{
	return (first.x - origin.x)  * (second.y - origin.y)  -  (first.y - origin.y) * (second.x - origin.x);
}


std::vector<Point> ConvexHull::GiftWrapping(const std::vector<Point>& points)
{
	Point pointOnHull{INT_MAX, INT_MAX};
	for(auto point : points)
	{
		 if(point < pointOnHull)
			 pointOnHull = point;
	}
	
	std::vector<Point> hull;
	
	Point  endPoint;
	do
	{
		if(hull.size() > 2)
		{
			if(CrossProduct(hull[hull.size()-2], hull.back(), pointOnHull) == 0)
			{
				int newDistance = (pointOnHull.x - hull[hull.size()-2].x) + (pointOnHull.y - hull[hull.size()-2].y);
				int oldDistance = (hull.back().x - hull[hull.size()-2].x) - (hull.back().y - hull[hull.size()-2].y);
				if(newDistance > oldDistance)
					hull.pop_back();
			}
		}
		
		hull.push_back(pointOnHull);
		endPoint = points[0];
		
		for(std::size_t j =1; j < points.size(); ++j)
		{
			if( (endPoint == pointOnHull) || (CrossProduct(hull.back(), endPoint, points[j]) > 0))
				endPoint = points[j];
		}
		pointOnHull = endPoint;
	}
	while(!(endPoint == hull.front()));
	
	if(CrossProduct(hull[hull.size()-2], hull.back(), hull.front()) == 0)
	{
		int newDistance = (hull.front().x - hull[hull.size()-2].x) + (hull.front().y - hull[hull.size()-2].y);
		int oldDistance = (hull.back().x - hull[hull.size()-2].x) - (hull.back().y - hull[hull.size()-2].y);
		if(newDistance > oldDistance)
			hull.pop_back();
	}
	
	std::cout << hull.size() << "\n";
	for(auto point : hull)
		std::cout << point;
	
	return hull;
}



std::vector<Point> ConvexHull::MonotoneChain(std::vector<Point>& points)
{
	std::size_t iterator = 0;
	std::vector<Point> hull(points.size() * 2);
	
	std::sort(points.begin(), points.end());
	
	for(std::size_t i = 0; i < points.size(); ++i)
	{
		while(iterator >= 2 && CrossProduct(hull[iterator-2], hull[iterator-1], points[i]) <= 0)
			--iterator;
			
		hull[iterator++] = points[i];
	}
	
	std::size_t t = iterator + 1;
	for(int i = points.size() - 2/*,  t = iterator + 1*/; i >= 0; --i)
	{
		while(iterator >= t && CrossProduct(hull[iterator-2], hull[iterator-1], points[i])  <= 0)
			--iterator;
			
		hull[iterator++] = points[i];
	}
	
	hull.resize(iterator-1);
	
	std::cout << hull.size() << '\n';
	for(auto point : hull)
		std::cout << point;
	
	return hull;
}



std::vector<Point> ConvexHull::FindHull(const std::vector<Point>& points, Point begin, Point end)
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

std::vector<Point> ConvexHull::Quickhull(const std::vector<Point>& points)
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