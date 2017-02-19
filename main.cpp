#include <iostream>
#include <Shape.hpp>
#include <Point.hpp>
#include <Line.hpp>
#include <Ellipse.hpp>
#include <Polygon.hpp>
#include <Circle.hpp>


int main() {
    Point p(3,3);
    Point p2(4,3);
    Point p3(3,4);
    Ellipse e(p,p2,p3);
    std::cout << e.dist_origin() << std::endl;
    return 0;
}