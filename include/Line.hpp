//
// Created by kev on 17/02/17.
//

#ifndef DRAWSHEEP_LINE_HPP
#define DRAWSHEEP_LINE_HPP
#include <Point.hpp>
#include <Shape.hpp>


class Line : public Shape {
private:
    Point A;
    Point B;
public:
    Line(const Point & p1,const Point & p2);
    virtual ~Line();
    virtual void draw(std::ostream &os = std::cout) const;
    virtual float area() const;
    virtual float perimeter() const;
    virtual float dist_origin() const;
    float dist_point(Point p) const;
    Point projete_orthog(Point p) const;
};


#endif //DRAWSHEEP_LINE_HPP
