#include <iostream>
#include <Shape.hpp>
#include <Point.hpp>
#include <Line.hpp>
#include <Ellipse.hpp>
#include <Polygon.hpp>
#include <Circle.hpp>


int main() {
    Point p;
    Point p2(20.0f,30.0f);
    Circle c(p2,20);
    c.draw(std::cout);
    Ellipse e(p2,50,20,20);
    e.draw(std::cout);
    return 0;
}