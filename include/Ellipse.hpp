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
    Point center;
    Point point_short_ray;
    Point point_long_ray;
public:
    Ellipse(const Point & cent,const Point & point_short,const Point & point_long);
    virtual ~Ellipse();
    virtual void draw(std::ostream &os = std::cout) const;
    virtual float area() const;
    virtual float perimeter() const;
};

#endif //DRAWSHEEP_ELLIPSE_HPP
