//
// Created by kev on 17/02/17.
//

#include <Line.hpp>

Line::Line(const Point & p1, const Point &p2):A(p1),B(p2)
{
}

Line::~Line(){}

void Line::draw(std::ostream & os) const {
    os << "drawline" << std::endl;
}

float Line::area() const{
    return 0.0f;
}

float Line::perimeter() const {
    return distance(A,B);
}

float Line::dist_origin() const{
    Point origin;
    return dist_point(origin);
}

float Line::dist_point(Point p) const {
    Point h = projete_orthog(p);
    //h contenu dans le segment AB
    if(A.get_x() < B.get_x() && h.get_x() > A.get_x() && h.get_x() < B.get_x() || A.get_x() > B.get_x() && h.get_x() > B.get_x() && h.get_x() < A.get_x()){
        return distance(h,p);
    }
    else{
        float dist_a = distance(A,p);
        float dist_b = distance(B,p);
        return dist_a < dist_b ? dist_a : dist_b;
    }
}

Point Line::projete_orthog(Point p) const{

    float xa = A.get_x();
    float ya = A.get_y();
    float xb = B.get_x();
    float yb = B.get_y();
    float xp = p.get_x();
    float yp = p.get_y();
    if(xa == 0){
        std::cout << "divpar0 n°1" << std::endl;
    }
    if(-xb/xa+1 == 0){
        std::cout << "divpar0 n°2" << std::endl;
    }
    float b = (yb-ya*xb/xa)/(-xb/xa+1);
    float a = (ya -  b)/ xa;
    if((xa-xb+(ya-yb)*a) == 0){
        std::cout << "divpar0 n°3" << std::endl;
    }
    float c = xp*xb+yp*yb-xp*xa-yp*ya;
    float xh = (-(ya-yb)*b - c) / (xa-xb+(ya-yb)*a);
    float yh = a*xh+b;
    Point h = Point(xh,yh);
    std::cout << "h : " << h << std::endl;
    return h;
}