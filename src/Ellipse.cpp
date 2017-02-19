//
// Created by kev on 17/02/17.
//

#include <Ellipse.hpp>

Ellipse::Ellipse(const Point & cent,const Point & point_short,const Point & point_long):center(cent),point_short_ray(point_short),point_long_ray(point_long)
{
}

Ellipse::~Ellipse(){}

void Ellipse::draw(std::ostream & os) const {
    os << "drawEllipse " << std::endl;
}

//approximation du perimetre
float Ellipse::perimeter() const{
    float rayA = distance(center,point_short_ray);
    float rayB = distance(center,point_long_ray);
    return M_PI*sqrt(2*(rayA*rayA+rayB*rayB));
}

float Ellipse::area() const{
    float rayA = distance(center,point_short_ray);
    float rayB = distance(center,point_long_ray);
    return M_PI*rayA*rayB;
}