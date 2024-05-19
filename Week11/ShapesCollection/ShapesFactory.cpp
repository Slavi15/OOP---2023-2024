#include "ShapesFactory.h"

#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"

// FACTORY based on user input
Shapes* ShapesFactory::createShape()
{
    size_t N;
    std::cin >> N;

    if (N == 1)
    {
        int x1, y1, x2, y2, x3, y3;
        std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        return new Triangle(x1, y1, x2, y2, x3, y3);
    }
    else if (N == 2)
    {
        int x1, y1, x3, y3;
        std::cin >> x1 >> y1 >> x3 >> y3;
        return new Rectangle(x1, y1, x3, y3);
    }
    else if (N == 3)
    {
        int x, y;
        double radius;

        std::cin >> x >> y >> radius;
        return new Circle(x, y, radius);
    }

    return nullptr;
}
