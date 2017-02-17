//
// Created by kev on 17/02/17.
//

#include <Ellipse.hpp>

Ellipse::Ellipse(const Point & cent,const float &ra,const float &rb ,const float &anglerot):center(cent),rayA(ra),rayB(rb),angleRotation(anglerot)
{
}

Ellipse::~Ellipse(){}

void Ellipse::draw(std::ostream & os) const {
    os << "drawEllipse " << std::endl;
}

float Ellipse::perimeter() const{
    return M_PI*sqrt(2*(rayA*rayA+rayB*rayB));
}

float Ellipse::area() const{
    return M_PI*rayA*rayB;
}