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
    Point point_X_ray;
    Point point_Y_ray;
public:
    Ellipse(const Point & cent,const Point & point_X,const Point & point_Y);
    virtual ~Ellipse();
    virtual void draw(std::ostream &os = std::cout) const;
    virtual float area() const;
    virtual float perimeter() const;
    virtual float dist_origin() const;
};

#endif //DRAWSHEEP_ELLIPSE_HPP
