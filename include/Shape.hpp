//
// Created by kev on 17/02/17.
//

#ifndef DRAWSHEEP_SHAPE_HPP
#define DRAWSHEEP_SHAPE_HPP
#include<iostream>

class Shape{
public:
    virtual void draw(std::ostream &os = std::cout) const = 0;//pour le moment draw sur terminal
    virtual float area() const = 0;
    virtual float perimeter() const = 0;
    virtual ~Shape(){};

};

#endif //DRAWSHEEP_SHAPE_HPP
