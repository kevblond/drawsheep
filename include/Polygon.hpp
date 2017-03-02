//
// Created by kev on 17/02/17.
//

#ifndef DRAWSHEEP_POLYGON_HPP
#define DRAWSHEEP_POLYGON_HPP
#include <My_Shape.hpp>
#include <vector>


class Polygon : public My_Shape {
private:
    std::vector<Point> vertices;
public:
    Polygon(std::vector<Point> v);
    virtual ~Polygon();
    virtual void draw(std::ostream &os = std::cout) const;
    virtual float area() const;
    virtual float perimeter() const;
    virtual float dist_origin() const;
    virtual void translate(float x, float y);
    virtual void scale(float s);
    virtual void rotate(float angle);
    virtual void central_sym(Point c_sym);
    virtual void axial_sym(Point p_origin_axis, Point p_extremity_axis);

    Point gravity_center() const;
};


#endif //DRAWSHEEP_POLYGON_HPP
