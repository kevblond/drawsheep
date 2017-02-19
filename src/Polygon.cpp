//
// Created by kev on 17/02/17.
//

#include <Polygon.hpp>

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
    for(int i = 0,j = vertices.size()-1 ; i < vertices.size() ; j=i++){
        area += (vertices[j].get_x() + vertices[i].get_x()) * (vertices[j].get_y() - vertices[i].get_y());
    }
    return std::abs(area/2.0);
}

//calcul la somme des distances entre tout les points du polygone
float Polygon::perimeter() const{
    float sum_dist = 0;
    for(int i = 0,j = vertices.size()-1 ; i < vertices.size() ; j=i++){
        sum_dist += distance(vertices[i],vertices[j]);
    }
    return sum_dist;
}