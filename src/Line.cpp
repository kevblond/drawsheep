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

void Line::translate(float x, float y){
    Point p(x,y);
    A+=p;
    B+=p;
}

void Line::scale(float s){
    if(s < 0){
        s=-s;
    }
    A*=s;
    B*=s;
}


void Line::rotate(float angle){
    Point mid_point = milieu_segment();
    //rotation depuis l'origine plus facile

    translate(-mid_point.get_x(),-mid_point.get_y());
    //{
    //rotation dans le meme sens peut importe A et B
    if(A.get_x() < B.get_x()){
        B = Point(B.get_x()*cosf(angle)-B.get_y()*sinf(angle),B.get_y()*cosf(angle)+B.get_x()*sinf(angle));
        A = Point(A.get_x()*cosf(-angle)-A.get_y()*sinf(-angle),A.get_y()*cosf(-angle)+A.get_x()*sinf(-angle));
    }
    else{
        B = Point(B.get_x()*cosf(-angle)-B.get_y()*sinf(-angle),B.get_y()*cosf(-angle)+B.get_x()*sinf(-angle));
        A = Point(A.get_x()*cosf(angle)-A.get_y()*sinf(angle),A.get_y()*cosf(angle)+A.get_x()*sinf(angle));
    }
    //}
    translate(mid_point.get_x(),mid_point.get_y());
}

Point Line::milieu_segment() const{
    return Point((A.get_x()+B.get_x())/2,(A.get_y()+B.get_y())/2);
}