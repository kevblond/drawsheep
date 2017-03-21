//
// Created by kev on 17/02/17.
//

#include <Polygon.hpp>
#include <Line.hpp>
#include <fstream>
#define MAX 400000

/**
 * constructeur du polygone, exception si il n'y a pas assez d'argument
 * @param v liste de point du polygone
 * @param c couleur interne
 * @param p contour
 */
Polygon::Polygon(std::vector<Point> v, QColor c ,QPen p)throw()
{
    if(v.size() < 3){
        throw "few argument, need 3 point for building a polygon";
    }
    vertices = v;
    this->color = c;
    this->pen = p;
}

Polygon::~Polygon(){}

/**
 * aire de la figure
 * @return aire
 */
float Polygon::area() const{
    float area = 0;
    for(unsigned long i = 0,j = vertices.size()-1 ; i < vertices.size() ; j=i++){
        area += (vertices[j].get_x() + vertices[i].get_x()) * (vertices[j].get_y() - vertices[i].get_y());
    }
    return std::abs(area/2.0f);
}

/**
 * perimètre de la figure
 * @return périmètre
 */
float Polygon::perimeter() const{
    float sum_dist = 0;
    for(unsigned long i = 0,j = vertices.size()-1 ; i < vertices.size() ; j=i++){
        sum_dist += distance(vertices[i],vertices[j]);
    }
    return sum_dist;
}

/**
 * distance entre la figure et le point d'origine
 * @return distance figure/origine
 */
float Polygon::dist_origin() const{
    Point origin;
    float dist_min = MAX;
    for(unsigned long i = 0,j = vertices.size()-1 ; i < vertices.size() ; j=i++){
        Line l(vertices[i],vertices[j]);
        float dist_line = l.dist_point(origin);
        if(dist_line < dist_min){
            dist_min = dist_line;
        }
    }
    return dist_min;
}

/**
 * translation de la figure par les coordonnées (x,y)
 * @param x coordonnée x
 * @param y coordonnée y
 */
void Polygon::translate(float x, float y){
    Point p(x,y);
    for(unsigned long i = 0 ; i < vertices.size() ; i++){
        vertices[i] += p;
    }
}


/**
 * ATTENTION : scale non fonctionnel
 * @param s
 */
void Polygon::scale(float s){
//    Point center = gravity_center();
//    for(unsigned long i=0 ; i < vertices.size() ; i++){
//        if(center.get_x() < vertices[i].get_x()){
//            if(center.get_y() < vertices[i].get_y()){
//                vertices[i]*=s;
//            }
//            else{
//                float yP = vertices[i].get_y() - (vertices[i].get_y()*s - vertices[i].get_y());
//                vertices[i] = Point(vertices[i].get_x()*s,yP);
//            }
//        }
//        else{
//            if(center.get_y() < vertices[i].get_y()){
//                float xP = vertices[i].get_x() - (vertices[i].get_x()*s - vertices[i].get_x());
//                vertices[i] = Point(xP,vertices[i].get_y()*s);
//            }
//            else{
//                float xP = vertices[i].get_x() - (vertices[i].get_x()*s - vertices[i].get_x());
//                float yP = vertices[i].get_y() - (vertices[i].get_y()*s - vertices[i].get_y());
//                vertices[i] = Point(xP,yP);
//            }
//        }
//    }
}


/**
 * reférence du scale, c'est à dire que cette fonction
 * sera utilisé pour calculer l'argument à donner pour le scale.
 * @return référence pour le scale
 */
float Polygon::ref_scale() const {
    float max_distance = 0;
    Point center = gravity_center();
    for(Point p : vertices){
        float dist = distance(p,center);
        max_distance = max_distance < dist ? dist : max_distance;
    }
    return max_distance;
}

/**
 * rotation de la figure par l'angle ang
 * @param ang angle de rotation
 */
void Polygon::rotate(float angle){
    Point center = gravity_center();
    translate(-center.get_x(),-center.get_y());
    for(unsigned long i = 0 ; i < vertices.size() ; i++){
        vertices[i] = Point(vertices[i].get_x()*cosf(angle)-vertices[i].get_y()*sinf(angle),vertices[i].get_y()*cosf(angle)+vertices[i].get_x()*sinf(angle));
    }
    translate(center.get_x(),center.get_y());
}

/**
 * renvoie du centre de la figure
 * @return point du centre de la figure
 */
Point Polygon::center() const {
    return gravity_center();
}

/**
 * applique une symétrie centrale à la figure par le point c_sym
 * @param c_sym point central de la symétrie
 */
void Polygon::central_sym(Point c_sym){
    for(unsigned long i = 0 ; i < vertices.size() ; i++){
        vertices[i].central_sym(c_sym);
    }
}

/**
 *  applique une symétrie axiale à la figure par la droite passant par les deux points en paramètre
 * @param p_origin_axis origine de la droite
 * @param p_extremity_axis extrémité de la droite
 */
void Polygon::axial_sym(Point p_origin_axis, Point p_extremity_axis){
    for(unsigned long i = 0 ; i < vertices.size() ; i++){
        vertices[i].axial_sym(p_origin_axis,p_extremity_axis);
    }
}

/**
 * calcul du centre de gravité du polygone
 * @return point du centre de gravité
 */
 Point Polygon::gravity_center() const{
    float s1 = 0;
    Point s2(0,0);
    for(unsigned long i = 0,j = vertices.size() - 1 ; i < vertices.size() ; j = i++){
        float t = vertices[j].get_x() * vertices[i].get_y() - vertices[j].get_y() * vertices[i].get_x();
        s1+=t;
        s2+=(vertices[j] + vertices[i])*t;
    }
    s1*=3;
    s2*= (1 / s1);
    return s2;
}

/**
 *  renvoie le type de la figure, utilisé pour différencier les figures
 * @return entier représentant le type de la figure
 */
int Polygon::type() const{
    return 5;
}

/**
 * modifie la couleur interne de la figure
 * @param c couleur
 */
void Polygon::setBrush(QColor c) {
    color = c;
}

/**
 * modifie la couleur du contour de la figure
 * @param p QPen du contour de la figure
 */
void Polygon::setPen(QPen p) {
    pen = p;
}

/**
 *  calcul et renvoie l'item représentant la figure pour la scene
 * @return pointeur vers un nouveau QGraphicsItem représentant la figure
 */
QGraphicsItem* Polygon::getItem() const{
    QVector<QPointF> v;
    for(Point p : vertices){
        v.push_back(QPointF(p.get_x(),p.get_y()));
    }
    QGraphicsPolygonItem *p = new QGraphicsPolygonItem(v);
    p->setBrush(QBrush(color));
    p->setPen(pen);
    return p;
}

/**
 * sauvegarde les données de la figure dans un fichier
 * @param filename nom du fichier
 */
void Polygon::save_to_file(const char *filename) {
    std::fstream file;

    file.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);


    // If file does not exist, Create new file
    if (!file ) {
        std::cout << "Cannot open file, file does not exist. Creating new file..";

        file.open(filename,  std::fstream::in | std::fstream::out | std::fstream::trunc);
    }
    file << type() << "\n";
    file << vertices.size() << "\n";
    for (Point p : vertices) {
        file << p.get_x() << " " << p.get_y() << "\n";
    }
    int r, g, b, a;
    color.getRgb(&r, &g, &b, &a);
    file << r << " " << g << " "<< b << " " << a << "\n";
    file.close();

}