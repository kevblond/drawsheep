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
    virtual void translate(float x, float y);
    virtual void scale(float s);
    virtual void rotate(float angle);
    virtual void central_sym(Point c_sym);
    virtual void axial_sym(Point p_origin_axis, Point p_extremity_axis);

    Point milieu_segment() const;
    float dist_point(Point p) const;
    Point projete_orthog(Point p) const;
};


#endif //DRAWSHEEP_LINE_HPP
