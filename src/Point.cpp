//
// Created by kev on 17/02/17.
//

#include <Point.hpp>
Point::Point(float a, float b):x(a),y(b)
{
}

std::ostream & operator<< (std::ostream & os, const Point & p)
{
    os << '(' << p.x << ',' << p.y << ')';
    return os;
}