//
// Created by kev on 17/02/17.
//

#ifndef DRAWSHEEP_CIRCLE_HPP
#define DRAWSHEEP_CIRCLE_HPP
#include<Point.hpp>
#include <Shape.hpp>
#include<cmath>

class Circle : public Shape {
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
};


#endif //DRAWSHEEP_CIRCLE_HPP
