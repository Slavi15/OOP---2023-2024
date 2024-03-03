#include <iostream>

using std::cin;
using std::cout;
using std::endl;

namespace Points
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
		cout << p.x << ' ' << p.y << endl;
	}
}

namespace Triangles
{
	using namespace Points;

	struct Triangle
	{
		Point p1;
		Point p2;
		Point p3;
	};

	void readTriangle(Triangle& triangle)
	{
		readPoint(triangle.p1);
		readPoint(triangle.p2);
		readPoint(triangle.p3);
	}

	double getSideLength(const Point& p1, const Point& p2)
	{
		double dx = p1.x - p2.x;
		double dy = p2.x - p2.y;

		return sqrt(dx * dx + dy * dy);
	}

	double getPerimeter(const Triangle& triangle)
	{
		return getSideLength(triangle.p1, triangle.p2) + getSideLength(triangle.p1, triangle.p3) + getSideLength(triangle.p2, triangle.p3);
	}

	double getTriangleArea(const Triangle& triangle)
	{
		double halfPerimeter = getPerimeter(triangle) / 2;

		return sqrt(halfPerimeter *
			(halfPerimeter - getSideLength(triangle.p1, triangle.p2)) *
			(halfPerimeter - getSideLength(triangle.p1, triangle.p3)) *
			(halfPerimeter - getSideLength(triangle.p2, triangle.p3)));
	}

	void sortTrianglesArea(Triangle* trianglesArray, size_t N)
	{
		if (!trianglesArray)
			return;

		unsigned int* areas = new unsigned int[N];

		for (size_t i = 0; i < N; i++)
			areas[i] = getTriangleArea(trianglesArray[i]);

		// Selection Sort <=> minimum swaps
		for (size_t i = 0; i < N; i++)
		{
			size_t minIndex = i;

			for (size_t j = i + 1; j < N; j++)
				if (areas[j] < areas[minIndex])
					minIndex = j;

			if (minIndex != i)
			{
				std::swap(areas[i], areas[minIndex]);
				std::swap(trianglesArray[i], trianglesArray[minIndex]);
			}
		}

		delete[] areas;
	}

	void printTriangle(const Triangle& triangle)
	{
		cout << "Point 1: " << triangle.p1.x << ' ' << triangle.p1.y << endl;
		cout << "Point 2: " << triangle.p2.x << ' ' << triangle.p2.y << endl;
		cout << "Point 3: " << triangle.p3.x << ' ' << triangle.p3.y << endl;
	}
}

int main()
{
	unsigned int N;
	cin >> N;

	Triangles::Triangle* trianglesArray = new Triangles::Triangle[N];

	for (size_t i = 0; i < N; i++)
		Triangles::readTriangle(trianglesArray[i]);

	for (size_t i = 0; i < N; i++)
	{
		cout << "Triangle " << i << endl;
		Triangles::printTriangle(trianglesArray[i]);
	}

	delete[] trianglesArray;
}