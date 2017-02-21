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

    Point p(3,3);
    float rx = 2;
    float ry = 2;
    Ellipse e(p,rx,ry);

    Line l(Point(12,3),Point(5,8));
    Point p2(1,5);
    std::cout << l.dist_point(p2) << std::endl;
    std::cout << l.dist_point(p) << std::endl;
    return app.exec();
}