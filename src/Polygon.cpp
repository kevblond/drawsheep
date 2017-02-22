//
// Created by kev on 17/02/17.
//

#include <Polygon.hpp>
#include <include/Line.hpp>

Polygon::Polygon(std::vector<Point> v)
{
    try{
        if(v.size() < 3){
            throw std::string("Error : polygon need 3 point");
        }
        vertices = v;
    }catch(std::string const& chaine){
        std::cerr << chaine << std::endl;
    }
}

Polygon::~Polygon(){}

void Polygon::draw(std::ostream & os) const {
    os << "drawPolygon" << std::endl;
}

//triangulation pour l'aire
float Polygon::area() const{
    float area = 0;
    for(unsigned long i = 0,j = vertices.size()-1 ; i < vertices.size() ; j=i++){
        area += (vertices[j].get_x() + vertices[i].get_x()) * (vertices[j].get_y() - vertices[i].get_y());
    }
    return std::abs(area/2.0f);
}

//calcul la somme des distances entre tout les points du polygone
float Polygon::perimeter() const{
    float sum_dist = 0;
    for(unsigned long i = 0,j = vertices.size()-1 ; i < vertices.size() ; j=i++){
        sum_dist += distance(vertices[i],vertices[j]);
    }
    return sum_dist;
}

float Polygon::dist_origin() const{
    Point origin;
    float dist_min = 400000;
    for(unsigned long i = 0,j = vertices.size()-1 ; i < vertices.size() ; j=i++){
        Line l(vertices[i],vertices[j]);
        float dist_line = l.dist_point(origin);
        if(dist_line < dist_min){
            dist_min = dist_line;
        }
    }
    return dist_min;
}

void Polygon::translate(float x, float y){
    Point p(x,y);
    for(unsigned long i = 0 ; i < vertices.size() ; i++){
        vertices[i] += p;
    }
}


void Polygon::scale(float s){
    for(Point p_it : vertices){
        p_it *= s;
    }
}


void Polygon::rotate(float angle){
    Point center = gravity_center();
    std::cout << center << std::endl;
    translate(-center.get_x(),-center.get_y());
    for(unsigned long i = 0 ; i < vertices.size() ; i++){
        vertices[i] = Point(vertices[i].get_x()*cosf(angle)-vertices[i].get_y()*sinf(angle),vertices[i].get_y()*cosf(angle)+vertices[i].get_x()*sinf(angle));
    }
    translate(-center.get_x(),-center.get_y());
}

void Polygon::central_sym(Point c_sym){
    for(unsigned long i = 0 ; i < vertices.size() ; i++){
        vertices[i].central_sym(c_sym);
    }
}

Point Polygon::gravity_center() const{
    float xg = 0;
    float yg = 0;
    for(unsigned int i = 0 ; i < vertices.size() - 1 ; i++){
        xg += (vertices[i].get_x() + vertices[i+1].get_x()) * (vertices[i].get_x()*vertices[i+1].get_y() - vertices[i+1].get_x()*vertices[i].get_y());
        yg += (vertices[i].get_y() + vertices[i+1].get_y()) * (vertices[i].get_x()*vertices[i+1].get_y() - vertices[i+1].get_x()*vertices[i].get_y());
    }
    xg *= 1/(6*area());
    yg *= 1/(6*area());
    return Point(xg,yg);
}