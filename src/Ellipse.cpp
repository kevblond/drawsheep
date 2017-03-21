//
// Created by kev on 17/02/17.
//

#include <Ellipse.hpp>
#include <fstream>

/**
 *  constructeur de l'ellipse
 *  @param cent centre
 *  @param rA rayon horizontal
 *  @param rB rayon vertical
 *  @param angle angle de rotation
 *  @param c couleur interne
 *  @param p couleur contour
 */
Ellipse::Ellipse(const Point & cent,float rA,float rB,float angle,QColor c, QPen p):c(cent),rayA(rA),rayB(rB),angle(angle)
{
    this->color = c;
    this->pen = p;
}

Ellipse::~Ellipse(){}

/**
 * perimètre de la figure
 * @return périmètre
 */
float Ellipse::perimeter() const{
    //pour l'ellipse le périmètre est une approximation
    return (float)M_PI*sqrtf(2*(rayA*rayA+rayB*rayB));
}

/**
 * aire de la figure
 * @return aire
 */
float Ellipse::area() const{
    return (float)M_PI*rayA*rayB;
}

/**
 * distance entre la figure et le point d'origine
 * @return distance figure/origine
 */
float Ellipse::dist_origin() const{
    Point origin;
    float x0 = c.get_x();
    float y0 = c.get_y();
    float Ac = rayA*rayA;
    float Bc = rayB*rayB;
    //si l'origine est contenu dans l'ellipse
    if((x0*cos(angle)+y0*sin(angle))*(x0*cos(angle)+y0*sin(angle)) / Ac + (-x0*sin(angle)+y0*cos(angle))*(-x0*sin(angle)+y0*cos(angle)) / Bc <= 1){
        return 0;
    }
    //coef directeur de la droite origin-centre
    float a = x0==0 ? 0 : y0 / x0;
    //delta de l'équation du second degré de la première equation du système à deux équations produit pour le calcul.
    float delta = 8 * Bc * x0 * Ac * a * y0 - 4 * Bc * Ac * y0*y0 + 4 * Ac * Bc*Bc - 4 * Ac * a*a * Bc * x0*x0 + 4 * Ac*Ac * a*a * Bc;
    if(delta < 0){
        throw "delta < 0 distance origin";
    }
    //calcul de la distance entre l'origine et le point (x_inc,y_inc) qui représente le point de l'ellipse le plus proche de l'origine.
    if(delta == 0){
        float x = 2*Bc*x0+2*Ac*a*y0 / (2*Bc + 2*Ac*a*a);
        float y = a*x;
        //prise en compte de l'angle
        float x_inc = x * cosf(angle) + y * sinf(angle);
        float y_inc = -x * sinf(angle) + y * cosf(angle);
        return distance(Point(x_inc,y_inc),origin);
    }
    float x1_cart = (2*Bc*x0+2*Ac*a*y0 - sqrtf(delta)) / (2*Bc + 2*Ac*a*a);
    float y1_cart = a*x1_cart;
    float x2_cart = (2*Bc*x0+2*Ac*a*y0 + sqrtf(delta)) / (2*Bc + 2*Ac*a*a);
    float y2_cart = a*x2_cart;

    //prise en compte de l'angle
    float x1_inc = x1_cart * cosf(angle) + y1_cart * sinf(angle);
    float y1_inc = -x1_cart * sinf(angle) + y1_cart * cosf(angle);
    float x2_inc = x2_cart * cosf(angle) + y2_cart * sinf(angle);
    float y2_inc = -x2_cart * sinf(angle) + y2_cart * cosf(angle);

    Point intersect1(x1_inc,y1_inc);
    Point intersect2(x2_inc,y2_inc);
    float dist_1 = distance(intersect1,origin);
    float dist_2 = distance(intersect2,origin);

    return dist_1 < dist_2 ? dist_1 : dist_2;

}

/**
 * translation de la figure par les coordonnées (x,y)
 * @param x coordonnée x
 * @param y coordonnée y
 */
void Ellipse::translate(float x, float y){
    c += Point(x,y);
}

/**
 * agrandissement/rétrecissement de la figure
 * @param s valeur de l'agrandissement/rétrecissement
 */
void Ellipse::scale(float s){
    rayA *= s;
    rayB *= s;
}

/**
 * reférence du scale, c'est à dire que cette fonction
 * sera utilisé pour calculer l'argument à donner pour le scale.
 * @return référence pour le scale
 */
float Ellipse::ref_scale() const {
    return rayA>rayB?rayA:rayB;
}

/**
 * rotation de la figure par l'angle ang
 * @param ang angle de rotation
 */
void Ellipse::rotate(float ang){
    angle += ang;
}

/**
 * renvoie du centre de la figure
 * @return point du centre de la figure
 */
Point Ellipse::center() const {
    return c;
}

/**
 * applique une symétrie centrale à la figure par le point c_sym
 * @param c_sym point central de la symétrie
 */
void Ellipse::central_sym(Point c_sym){
    c.central_sym(c_sym);
}

/**
 *  applique une symétrie axiale à la figure par la droite passant par les deux points en paramètre
 * @param p_origin_axis origine de la droite
 * @param p_extremity_axis extrémité de la droite
 */
void Ellipse::axial_sym(Point p_origin_axis, Point p_extremity_axis){
    c.axial_sym(p_origin_axis,p_extremity_axis);
}

/**
 *  renvoie le type de la figure, utilisé pour différencier les figures
 * @return entier représentant le type de la figure
 */
int Ellipse::type() const{
    return 4;
}

/**
 * modifie la couleur interne de la figure
 * @param c couleur
 */
void Ellipse::setBrush(QColor c) {
    color = c;
}

/**
 * modifie la couleur du contour de la figure
 * @param p QPen du contour de la figure
 */
void Ellipse::setPen(QPen p) {
    pen = p;
}

/**
 *  calcul et renvoie l'item représentant la figure pour la scene
 * @return pointeur vers un nouveau QGraphicsItem représentant la figure
 */
QGraphicsItem* Ellipse::getItem() const{
    QGraphicsEllipseItem *e = new QGraphicsEllipseItem(c.get_x()-rayA,c.get_y()-rayB,rayA*2,rayB*2);
    e->setBrush(QBrush(color));
    e->setPen(pen);
    e->setTransformOriginPoint(c.get_x(),c.get_y());
    e->setRotation((angle*180)/M_PI);
    return e;
}

/**
 * sauvegarde les données de la figure dans un fichier
 * @param filename nom du fichier
 */
void Ellipse::save_to_file(const char *filename) {
    std::fstream file;

    file.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);


    // If file does not exist, Create new file
    if (!file ) {
        std::cout << "Cannot open file, file does not exist. Creating new file..";

        file.open(filename,  std::fstream::in | std::fstream::out | std::fstream::trunc);
    }
    file << type() << "\n";
    file << c.get_x() << " " << c.get_y() << "\n";
    file << rayA << " " << rayB << "\n";
    file << angle << "\n";
    int r, g, b, a;
    color.getRgb(&r, &g, &b, &a);
    file << r << " " << g << " "<< b << " " << a << "\n";
    file.close();

}


