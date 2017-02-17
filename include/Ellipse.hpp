//
// Created by kev on 17/02/17.
//

#ifndef DRAWSHEEP_ELLIPSE_HPP
#define DRAWSHEEP_ELLIPSE_HPP
#include<Point.hpp>
#include <Shape.hpp>
#include <cmath>


class Ellipse : public Shape{
private:
    //comment représenter une ellipse?
    Point center;
    float rayA;
    float rayB;
    float angleRotation;
public:
    Ellipse(const Point & cent,const float &ra,const float &rb,const float &anglerot);
    virtual ~Ellipse();
    virtual void draw(std::ostream &os = std::cout) const;
    virtual float area() const;
    virtual float perimeter() const;
};

#endif //DRAWSHEEP_ELLIPSE_HPP
