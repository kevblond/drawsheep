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


float Circle::dist_origin() const{
    Point origin;
    return distance(center,origin) - ray;
}

void Circle::translate(float x, float y) {
    center += Point(x,y);
}

void Circle::scale(float s){
    ray *= s;
}

void Circle::rotate(float angle){
    //rotation inutile
}


void Circle::central_sym(Point c_sym){
    center.central_sym(c_sym);
}