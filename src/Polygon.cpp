//
// Created by kev on 17/02/17.
//

#include <Polygon.hpp>

Polygon::Polygon()
{
}

Polygon::~Polygon(){}

void Polygon::draw(std::ostream & os) const {
    os << "drawPolygon" << std::endl;
}

float Polygon::area() const{
    return 0.0f;
}

float Polygon::perimeter() const{
    return 0.0f;
}