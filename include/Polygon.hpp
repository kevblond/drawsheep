//
// Created by kev on 17/02/17.
//

#ifndef DRAWSHEEP_POLYGON_HPP
#define DRAWSHEEP_POLYGON_HPP
#include <Shape.hpp>
#include<Point.hpp>


class Polygon : public Shape {
private:
    //comment représenter un polygone?
public:
    Polygon();
    virtual ~Polygon();
    virtual void draw(std::ostream &os = std::cout) const;
    virtual float area() const;
};


#endif //DRAWSHEEP_POLYGON_HPP
