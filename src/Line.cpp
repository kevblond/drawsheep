//
// Created by kev on 17/02/17.
//

#include <Line.hpp>

Line::Line(const Point & p1, const Point &p2):A(p1),B(p2)
{
}

Line::~Line(){}

void Line::draw(std::ostream & os) const {
    os << "drawline" << std::endl;
}

float Line::area() const{
    return 0.0f;
}

float Line::perimeter() const {
    return distance(A,B);
}

float Line::dist_origin() const{
    Point origin;
    float dist_A = distance(A,origin);
    float dist_B = distance(B,origin);
    return dist_A < dist_B ? dist_A : dist_B;
}