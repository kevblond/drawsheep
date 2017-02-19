//
// Created by kev on 17/02/17.
//

#include <Point.hpp>
Point::Point(float a, float b):x(a),y(b)
{
}

std::ostream & operator<< (std::ostream & os, const Point & p)
{
    os << '(' << p.x << ',' << p.y << ')';
    return os;
}

float distance(Point p1, Point p2){
    float dist_x = 0;
    float dist_y = 0;
    if(p1.x < p2.x){
        if(p1.y < p2.y){
            dist_x = p2.x - p1.x;
            dist_y = p2.y - p1.y;
        }
        else{
            dist_x = p2.x - p1.x;
            dist_y = p1.y - p2.y;
        }
    }
    else{
        if(p1.y < p2.y){
            dist_x = p1.x - p2.x;
            dist_y = p2.y - p1.y;
        }
        else{
            dist_x = p1.x - p2.x;
            dist_y = p1.y - p2.y;
        }
    }
    return sqrt(dist_x*dist_x + dist_y * dist_y);
}