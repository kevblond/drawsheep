//
// Created by kev on 17/02/17.
//

#include <Line.hpp>
#include <fstream>
/**
 * constructeur de la ligne
 * @param p1 premier point
 * @param p2 deuxième point
 * @param c couleur interne
 * @param p contour
 */
Line::Line(const Point & p1, const Point &p2, QColor c,QPen p):A(p1),B(p2)
{
    this->color = c;
    this->pen = p;
}

Line::~Line(){}

/**
 * aire de la figure
 * @return aire
 */
float Line::area() const{
    return 0.0f;
}

/**
* perimètre de la figure
* @return périmètre
*/
float Line::perimeter() const {
    return distance(A,B);
}

/**
 * distance entre la figure et le point d'origine
 * @return distance figure/origine
 */
float Line::dist_origin() const{
    Point origin;
    return dist_point(origin);
}

/**
 * distance entre la ligne et un point
 * @param p point
 * @return distance ligne/point
 */
float Line::dist_point(Point p) const {
    Point origin;
    //calcul du projetté orthogonal
    Point h = projete_orthog(p);
    //h contenu dans le segment AB
    if((A.get_x() < B.get_x() && h.get_x() > A.get_x() && h.get_x() < B.get_x()) || A.get_x() > (B.get_x() && h.get_x() > B.get_x() && h.get_x() < A.get_x())){
        return distance(h,p);
    }
    else{
        //si h n'appartient pas au segment AB, le point le plus proche est donc soit A soit B
        float dist_a = distance(A,p);
        float dist_b = distance(B,p);
        return dist_a < dist_b ? dist_a : dist_b;
    }
}

/**
 * projeté orthogonal d'un point sur la ligne
 * @param p point
 * @return point du projete orthogonal resultant
 */
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
    if(A.get_x() == B.get_x()){
        return Point(A.get_x(),p.get_y());
    }
    try{
        calc_equation_cart(a,b);
    }catch(std::string s){
        return Point(A.get_x(),p.get_y());
    }
    float c = xp*xb+yp*yb-xp*xa-yp*ya;
    float xh = (-(ya-yb)*b - c) / (xa-xb+(ya-yb)*a);
    float yh = a*xh+b;
    Point h = Point(xh,yh);
    return h;
}

/**
 * calcul de l'équation cartésienne ax+b de la ligne
 * @param a modifie le coefficient directeur
 * @param b modifie l'ordonnée à l'origine
 */
void Line::calc_equation_cart(float &a, float &b) const{
    if(A.get_x()==B.get_x()){
        throw "droite verticale";
    }
    a = (B.get_y()-A.get_y()) / (B.get_x()-A.get_x());
    b = A.get_y() - a * A.get_x();
}

/**
 * translation de la figure par les coordonnées (x,y)
 * @param x coordonnée x
 * @param y coordonnée y
 */
void Line::translate(float x, float y){
    Point p(x,y);
    A+=p;
    B+=p;
}

/**
 * ATTENTION : scale non fonctionnel
 * @param s
 */
void Line::scale(float s){
//    if(s < 0){
//        s=-s;
//    }
//    float a,b;
//    if(A.get_x() == B.get_x()){
//        B = Point(B.get_x(),A.get_y() + (B.get_y()-A.get_y())*s);
//        return;
//    }
//    calc_equation_cart(a,b);
//    float xb1,xb2,yb1,yb2;
//    float dist = distance(A,B);
//    float new_dist = s * dist;
//    float apol = a*a+1;
//    float bpol = -2*A.get_x() + a*a + 2*a*b - 2*a*A.get_y();
//    float cpol = -new_dist*new_dist + A.get_x()*A.get_x() + b*b -2*b*A.get_y() -A.get_y()*A.get_y();
//    float delta = bpol * bpol - 4 * apol * cpol;
//    if(delta<0){
//        return;
//    }
//    xb1 = fabsf((bpol - sqrtf(delta))/(2*apol));
//    yb1 = a*xb1+b;
//    xb2 = fabsf((bpol + sqrtf(delta))/(2*apol));
//    yb2 = a*xb2+b;
//    if(xb1 > A.get_x())
//    {
//        B = Point(xb1,yb1);
//    }
//    else{
//        B = Point(xb2,yb2);
//    }
}

/**
 * reférence du scale, c'est à dire que cette fonction
 * sera utilisé pour calculer l'argument à donner pour le scale.
 * @return référence pour le scale
 */
float Line::ref_scale() const {
    return distance(A,B);
}

/**
 * scale spécial pour la ligne
 * @param xb coordonnée x du clic de souris
 * @param yb coordonnée y du clic de souris
 */
void Line::scale_line(float xb,float yb){
    float a,b;
    //la ligne ne doit pas devenir un point
    if(A.get_x() == xb){
        return;
    }
    try{
        calc_equation_cart(a,b);
        //si la courbe part trop vers le bas, le scale se fais avec le y de la souris, sinon avec x.
        if(fabsf(a)>2){
            B = Point((yb-b)/a,yb);
        }
        else{
            B = Point(xb,a*xb+b);
        }
    }catch(std::string s){
        //le cas ou la ligne est vertical
        B = Point(B.get_x(),yb);
    }
}

/**
 * rotation de la figure par l'angle ang
 * @param ang angle de rotation
 */
void Line::rotate(float angle){
    Point mid_point = milieu_segment();
    //rotation depuis l'origine plus facile
    translate(-mid_point.get_x(),-mid_point.get_y());
    //rotation dans le meme sens peut importe A et B
    B = Point(B.get_x()*cosf(angle)-B.get_y()*sinf(angle),B.get_y()*cosf(angle)+B.get_x()*sinf(angle));
    A = Point(A.get_x()*cosf(angle)-A.get_y()*sinf(angle),A.get_y()*cosf(angle)+A.get_x()*sinf(angle));
    translate(mid_point.get_x(),mid_point.get_y());
}

/**
 * renvoie du centre de la figure
 * @return point du centre de la figure
 */
Point Line::center() const {
    return milieu_segment();
}

/**
 * applique une symétrie centrale à la figure par le point c_sym
 * @param c_sym point central de la symétrie
 */
void Line::central_sym(Point c_sym){
    A.central_sym(c_sym);
    B.central_sym(c_sym);
}


/**
 *  applique une symétrie axiale à la figure par la droite passant par les deux points en paramètre
 * @param p_origin_axis origine de la droite
 * @param p_extremity_axis extrémité de la droite
 */
void Line::axial_sym(Point p_origin_axis, Point p_extremity_axis){
    A.axial_sym(p_origin_axis,p_extremity_axis);
    B.axial_sym(p_origin_axis,p_extremity_axis);
}

/**
 * calcul du milieu de la ligne
 * @return point du milieu
 */
Point Line::milieu_segment() const{
    return Point((A.get_x()+B.get_x())/2,(A.get_y()+B.get_y())/2);
}

/**
 *  renvoie le type de la figure, utilisé pour différencier les figures
 * @return entier représentant le type de la figure
 */
int Line::type() const{
    return 6;
}

/**
 * modifie la couleur interne de la figure
 * @param c couleur
 */
void Line::setBrush(QColor c) {
    //pas de couleur de fond pour une ligne
}

/**
 * modifie la couleur du contour de la figure
 * @param p QPen du contour de la figure
 */
void Line::setPen(QPen p) {
    pen = p;
}

/**
 *  calcul et renvoie l'item représentant la figure pour la scene
 * @return pointeur vers un nouveau QGraphicsItem représentant la figure
 */
QGraphicsItem* Line::getItem() const{
    QGraphicsLineItem *l = new QGraphicsLineItem(A.get_x(),A.get_y(),B.get_x(),B.get_y());
    l->setPen(pen);
    return l;
}

/**
 * sauvegarde les données de la figure dans un fichier
 * @param filename nom du fichier
 */
void Line::save_to_file(const char *filename) {
    std::fstream file;

    file.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);


    // If file does not exist, Create new file
    if (!file ) {
        std::cout << "Cannot open file, file does not exist. Creating new file..";

        file.open(filename,  std::fstream::in | std::fstream::out | std::fstream::trunc);
    }
    file << type() << "\n";
    file << A.get_x() << " " << A.get_y() << "\n";
    file << B.get_x() << " " << B.get_y() << "\n";

    int r, g, b, a;
    color.getRgb(&r, &g, &b, &a);
    file << r << " " << g << " "<< b << " " << a << "\n";
    file.close();

}