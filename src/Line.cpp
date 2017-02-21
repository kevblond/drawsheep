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
    //calcul du projetté orthogonal
    Point h = projete_orthog(p);
    //h contenu dans le segment AB
    if(A.get_x() < B.get_x() && h.get_x() > A.get_x() && h.get_x() < B.get_x() || A.get_x() > B.get_x() && h.get_x() > B.get_x() && h.get_x() < A.get_x()){
        return distance(h,p);
    }
    else{
        //si h n'appartient pas au segment AB, le point le plus proche est donc soit A soit B
        float dist_a = distance(A,p);
        float dist_b = distance(B,p);
        return dist_a < dist_b ? dist_a : dist_b;
    }
}

Point Line::projete_orthog(Point p) const{
    if(A==B){
        return A;
    }
    float xa = A.get_x();
    float ya = A.get_y();
    float xb = B.get_x();
    float yb = B.get_y();
    float xp = p.get_x();
    float yp = p.get_y();
    float a;
    float b;
    //si B est sur l'ordonné
    if(xb == 0){
        b = yb;
        //si A est aussi sur l'ordonné
        if(xa == 0){
            //renvoyer le point le plus proche entre A et B
            return distance(p,A) > distance(p,B)?B:A;
        }
        else{
            a = (ya -  b)/ xa;
        }
    }
    else{
        //si a est sur l'ordonnée
        if(xa == 0){
            b = ya;

            //si AB va de gauche a droite
            if(xa < xb){
                a = (yb-ya) / xb ;
            }
            //si AB va de droite a gauche
            else{
                a = (ya-yb) / xb;
            }
        }
        //a et b calculé grace au système yA = a*xA+b et yB = a*xB+b
        else{
            b = (yb-ya*xb/xa)/(-xb/xa+1);
            a = (ya -  b)/ xa;
        }
    }
    float c = xp*xb+yp*yb-xp*xa-yp*ya;
    float xh = (-(ya-yb)*b - c) / (xa-xb+(ya-yb)*a);
    float yh = a*xh+b;
    Point h = Point(xh,yh);
    return h;
}