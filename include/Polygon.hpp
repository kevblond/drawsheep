//
// Created by kev on 17/02/17.
//

#ifndef DRAWSHEEP_POLYGON_HPP
#define DRAWSHEEP_POLYGON_HPP
#include <Shape.hpp>
#include <vector>


class Polygon : public Shape {
private:
    std::vector<Point> vertices;
public:
    Polygon(std::vector<Point> v);
    virtual ~Polygon();
    virtual void draw(std::ostream &os = std::cout) const;
    virtual float area() const;
    virtual float perimeter() const;
};


#endif //DRAWSHEEP_POLYGON_HPP
