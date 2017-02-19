#include <iostream>
#include <Shape.hpp>
#include <Point.hpp>
#include <Line.hpp>
#include <Ellipse.hpp>
#include <Polygon.hpp>
#include <Circle.hpp>


int main() {
    Point p;
    Point p2(3,3);
    Point p3(0,3);
    std::vector<Point> vecp;
    vecp.push_back(p);
    vecp.push_back(p2);
    vecp.push_back(p3);
    Polygon pol(vecp);
    std::cout << pol.area() << std::endl;
    std::cout << pol.perimeter() << std::endl;
    return 0;
}