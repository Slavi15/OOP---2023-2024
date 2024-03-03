#include <iostream>

using std::cin;
using std::cout;
using std::endl;

namespace PointsNS
{
	struct Point
	{
		double x, y;
	};

	void readPoint(Point& p)
	{
		cin >> p.x >> p.y;
	}

	void printPoint(const Point& p)
	{
		cout << "( " << p.x << " , " << p.y << " )" << endl;
	}

	double getDistanceFromCentre(const Point& p)
	{
		return sqrt(p.x * p.x + p.y * p.y);
	}

	double getDistanceBetweenPoints(const Point& p1, const Point& p2)
	{
		double dx = p1.x - p2.x;
		double dy = p1.y - p2.y;

		return sqrt(dx * dx + dy * dy);
	}

	unsigned int getQuadrant(const Point& p)
	{
		if (p.x == 0 || p.y == 0)
			return -1;

		if (p.x > 0 && p.y > 0)
			return 1;
		else if (p.x > 0 && p.y < 0)
			return 4;
		else if (p.x < 0 && p.y > 0)
			return 2;
		else
			return 3;
	}

	bool isInside(const Point& p, double radius)
	{
		double distance = getDistanceFromCentre(p);

		return distance < radius ? true : false;
	}
}

int main()
{
	PointsNS::Point point = { 0, 0 };
	PointsNS::readPoint(point);

	cout << PointsNS::getDistanceFromCentre(point) << endl;
	cout << PointsNS::getDistanceBetweenPoints({ 2, 4 }, { 3, 6 }) << endl;

	return 0;
}