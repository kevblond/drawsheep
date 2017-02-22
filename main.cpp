#include <iostream>
#include <Shape.hpp>
#include <Ellipse.hpp>
#include <Polygon.hpp>
#include <QApplication>
#include <QPushButton>
#include <Line.hpp>

// TODO Faire des tests unitaires, rapporte des points dans le rapport

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QPushButton drawing("Hello world!");

    drawing.setFixedSize(1500, 900);
    drawing.show();

//    Point p(3,3);
//    float rx = 2;
//    float ry = 2;
//    Ellipse e(p,rx,ry);

//    std::vector<Point> polyPoint;
//    polyPoint.push_back(Point(12,3));
//    polyPoint.push_back(Point(5,8));
//    polyPoint.push_back(Point(0,2));
//    polyPoint.push_back(Point(2,0));
//    Polygon pol(polyPoint);
//    std::cout << pol.dist_origin() << std::endl;
//    Line l(Point(0,2),Point(2,0));
//    std::cout << l.dist_origin() << std::endl;

    Line line(Point(3,3),Point(5,5));
    line.rotate(90);
    std::cout << line.milieu_segment() << std::endl;
    std::cout << line.dist_origin() << std::endl;
    return app.exec();
}