#include <iostream>
#include <Shape.hpp>
#include <Point.hpp>
#include <Line.hpp>
#include <Ellipse.hpp>
#include <Polygon.hpp>
#include <Circle.hpp>


int main() {
    std::cout << "Hello, World!" << std::endl;
    Point p;
    Point p2(20.0f,30.0f);
    Circle c(p,20);
    c.draw(std::cout);
    return 0;
}