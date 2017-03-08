//
// Created by kev on 17/02/17.
//

#ifndef DRAWSHEEP_LINE_HPP
#define DRAWSHEEP_LINE_HPP
#include <Point.hpp>
#include <My_Shape.hpp>


class Line : public My_Shape {
private:
    Point A;
    Point B;
public:
    Line(const Point & p1,const Point & p2);
    virtual ~Line();
    virtual int type() const;
    virtual void setBrush(QColor c);
    virtual void setPen(QPen p);
    virtual QGraphicsItem* getItem() const;
    virtual void draw(std::ostream &os = std::cout) const;
    virtual float area() const;
    virtual float perimeter() const;
    virtual float dist_origin() const;
    virtual void translate(float x, float y);
    virtual void rotate(float angle);
    virtual void scale(float s);
    virtual float ref_scale() const;
    virtual Point center() const;
    virtual void central_sym(Point c_sym);
    virtual void axial_sym(Point p_origin_axis, Point p_extremity_axis);

    void scale_line(float xb, float yb);
    void calc_equation_cart(float &a,float &b) const;
    Point milieu_segment() const;
    float dist_point(Point p) const;
    Point projete_orthog(Point p) const;
};


#endif //DRAWSHEEP_LINE_HPP
