//
// Created by kev on 17/02/17.
//

#ifndef DRAWSHEEP_POINT_HPP
#define DRAWSHEEP_POINT_HPP
#include<iostream>
#include<cmath>

class Point {
private:
    float x;
    float y;
public:
    Point(float a=0,float b=0);
    float get_x() const;
    float get_y() const;
    bool operator== (const Point & p) const;
    Point& operator+= (const Point &p);
    Point& operator*= (float s);
    Point& central_sym(Point c_sym);
    friend std::ostream & operator<< (std::ostream & os, const Point & p);
    friend float distance(Point p1,Point p2);
};


#endif //DRAWSHEEP_POINT_HPP
