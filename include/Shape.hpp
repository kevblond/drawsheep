//
// Created by kev on 17/02/17.
//

#ifndef DRAWSHEEP_SHAPE_HPP
#define DRAWSHEEP_SHAPE_HPP
#include<iostream>
#include<Point.hpp>

class Shape{
private:
    //mat3 matrix = matrice identité
    //utilisé pour les rotate translate etc...
public:
    virtual void draw(std::ostream &os = std::cout) const = 0;//pour le moment draw sur terminal
    virtual float area() const = 0;
    virtual float perimeter() const = 0;
    virtual float dist_origin() const = 0;
    virtual ~Shape(){};
//    virtual void rotate(float angle);
//    virtual void translate(float x, float y);
//    virtual void scale(float s);
//    virtual void central_sym(Point center);
//    virtual void axial_sym(Point p_origin_axis, Point p_extremity_axis);
};

#endif //DRAWSHEEP_SHAPE_HPP
