#include <iostream>
#include <Shape.hpp>
#include <Point.hpp>
#include <Line.hpp>
#include <Ellipse.hpp>
#include <Polygon.hpp>
#include <Circle.hpp>


int main() {
    Point p(3,3);
    float rx = 2;
    float ry = 2;
    Ellipse e(p,rx,ry);
    std::cout << e.dist_origin() << std::endl;
    return 0;
}