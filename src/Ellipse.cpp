//
// Created by kev on 17/02/17.
//

#include <Ellipse.hpp>

Ellipse::Ellipse(const Point & cent,const float &ra,const float &rb ):center(cent),rayA(ra),rayB(rb)
{
}

Ellipse::~Ellipse(){}

void Ellipse::draw(std::ostream & os) const {
    os << "drawEllipse" << std::endl;
}

float Ellipse::area() const{
    return M_PI*rayA*rayB;
}