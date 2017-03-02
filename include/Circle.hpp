//
// Created by kev on 17/02/17.
//

#ifndef DRAWSHEEP_CIRCLE_HPP
#define DRAWSHEEP_CIRCLE_HPP
#include<Point.hpp>
#include <My_Shape.hpp>
#include<cmath>

class Circle : public My_Shape {
private:
    Point center;
    float ray;
public:
    Circle(const Point &center,float ray);
    virtual ~Circle();
    virtual void draw(std::ostream & os = std::cout) const;
    virtual float area() const;
    virtual float perimeter() const;
    virtual float dist_origin() const;
    virtual void translate(float x, float y);
    virtual void scale(float s);
    virtual void rotate(float angle);
    virtual void central_sym(Point c_sym);
    virtual void axial_sym(Point p_origin_axis, Point p_extremity_axis);
};


#endif //DRAWSHEEP_CIRCLE_HPP
