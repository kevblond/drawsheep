//
// Created by kev on 17/02/17.
//

#include <Point.hpp>
#include <Line.hpp>

/**
 * constructeur du point
 * @param a coordonnée x
 * @param b coordonnée y
 */
Point::Point(float a, float b):x(a),y(b)
{
}

/**
 * renvoie la coordonnée x du point
 * @return coordonnée x
 */
float Point::get_x() const {
    return x;
}

/**
 * renvoie la coordonnée y du point
 * @return coordonnée y
 */
float Point::get_y() const {
    return y;
}

bool Point::operator== (const Point & p) const{
    return p.x == x && p.y == y;
}

Point& Point::operator+= (const Point & p) {
    x+=p.x;
    y+=p.y;
    return *this;
}

Point& Point::operator*= (float s) {
    x*=s;
    y*=s;
    return *this;
}

Point Point::operator+ (const Point& b) const{
    return Point(x+b.x,y+b.y);
}


Point Point::operator* (float t) const{
    return Point(t*x,t*y);
}

/**
 * calcul et renvoie le point resultant de sa symétrie centrale par le point c_sym
 * @param c_sym point central de la symétrie
 * @return point symétrique
 */
Point& Point::central_sym(Point c_sym){
    x = 2 * c_sym.x - x;
    y = 2 * c_sym.y - y;
    return *this;
}

/**
 * calcul et renvoie le point resultant de sa symétrie axiale
 * par la droite passant par les deux points en paramètre
 * @param p_origin_axis premier point de la droite
 * @param p_extremity_axis deuxième point de la droite
 * @return point symétrique par la droite
 */
Point& Point::axial_sym(Point p_origin_axis, Point p_extremity_axis){
    Line l(p_origin_axis,p_extremity_axis);
    Point transpose = l.projete_orthog(*this);
    return central_sym(transpose);
}

/**
 * calcul la distance entre deux points
 * @param p1 premier point
 * @param p2 deuxième point
 * @return distance premier/deuxième point
 */
float distance(Point p1, Point p2){
    float dist_x = fabsf(p2.x - p1.x);
    float dist_y = fabsf(p2.y - p1.y);
    return sqrtf(dist_x * dist_x + dist_y * dist_y);
}