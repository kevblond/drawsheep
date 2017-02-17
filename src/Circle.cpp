//
// Created by kev on 17/02/17.
//
#include <Circle.hpp>

Circle::Circle(const Point & center, float ray):center(center),ray(ray)
{
}

Circle::~Circle(){}

void Circle::draw(std::ostream & os) const {
    os << "drawCircle " << center << " " << ray << std::endl;
}

float Circle::area() const{
    return M_PI*ray*ray;
}

float Circle::perimeter() const{
    return M_PI*2*ray;
}