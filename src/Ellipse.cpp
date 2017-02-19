//
// Created by kev on 17/02/17.
//

#include <Ellipse.hpp>

Ellipse::Ellipse(const Point & cent,const Point & point_X,const Point & point_Y):center(cent),point_X_ray(point_X),point_Y_ray(point_Y)
{
}

Ellipse::~Ellipse(){}

void Ellipse::draw(std::ostream & os) const {
    os << "drawEllipse " << std::endl;
}

//approximation du perimetre
float Ellipse::perimeter() const{
    float rayA = distance(center,point_X_ray);
    float rayB = distance(center,point_Y_ray);
    return M_PI*sqrt(2*(rayA*rayA+rayB*rayB));
}

float Ellipse::area() const{
    float rayA = distance(center,point_X_ray);
    float rayB = distance(center,point_Y_ray);
    return M_PI*rayA*rayB;
}

float Ellipse::dist_origin() const{
    Point origin;
    float rayA = distance(center,point_X_ray);
    float rayB = distance(center,point_Y_ray);
    std::cout << "A :" << rayA << std::endl;
    std::cout << "B :" << rayB << std::endl;
    float x0 = center.get_x();
    float y0 = center.get_y();
    std::cout << "x0 : " << x0 << std::endl;
    std::cout << "y0 : " << y0 << std::endl;
    if(x0 == 0){
        return y0;
    }
    float a = x0 / y0;
    std::cout << "a : " << a << std::endl;
    //b = 0 pour la droite ax+b
    //eq ellipse : (x-x0)² / rayA² + (y-y0)² / rayB² = 1
    //eq line : y = a x
    //systeme a deux solution ( les deux intersections de lellipse avec la droite)
    // delta = 8B²x0A²ay0 - 4B²A²y0² - 4A²B⁴ - 4 A²a²B²x0² + 4A⁴a²B²
    // x1 = (2B²x0+2A²ay0 - sqrt(delta) ) / 2B² + 2A²a²  et y1 = ax1
    // x2 = (2B²x0+2A²ay0 + sqrt(delta) ) / 2B² + 2A²a²  et y2 = ax2
    float Ac = rayA*rayA;
    float Bc = rayB*rayB;
    std::cout << 8* Bc * x0 * Ac * a * y0 << std::endl;
    std::cout << - 4 * Bc * Ac * y0*y0 << std::endl;
    std::cout << - 4 * Ac * Bc*Bc << std::endl;
    std::cout << - 4 * Ac * a*a * Bc * x0*x0 << std::endl;
    std::cout <<  4 * Ac*Ac * a*a * Bc << std::endl;
    float delta = 8 * Bc * x0 * Ac * a * y0 - 4 * Bc * Ac * y0*y0 + 4 * Ac * Bc*Bc - 4 * Ac * a*a * Bc * x0*x0 + 4 * Ac*Ac * a*a * Bc;
    std::cout << "delta : " << delta << std::endl;
    if(delta < 0){
        std::cerr << "delta < 0 distance origin" << std::endl;
    }
    if(delta == 0){
        float x = 2*Bc*x0+2*Ac*a*y0 / 2*Bc + 2*Ac*a*a;
        float y = a*x;
        std::cout << Point(x,y) << std::endl;
        return distance(Point(x,y),origin);
    }
    float x1 = (2*Bc*x0+2*Ac*a*y0 - sqrtf(delta)) / 2*Bc + 2*Ac*a*a;
    float y1 = a*x1;
    float x2 = (2*Bc*x0+2*Ac*a*y0 + sqrtf(delta)) / 2*Bc + 2*Ac*a*a;
    float y2 = a*x2;

    Point intersect1(x1,y1);
    Point intersect2(x2,y2);
    std::cout << intersect1 << std::endl;
    std::cout << intersect2 << std::endl;
    float dist_1 = distance(intersect1,origin);
    float dist_2 = distance(intersect2,origin);

    return dist_1 < dist_2 ? dist_1 : dist_2;

}