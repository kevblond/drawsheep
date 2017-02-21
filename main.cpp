#include <iostream>
#include <Shape.hpp>
#include <Ellipse.hpp>
#include <Polygon.hpp>
#include <QApplication>
#include <QPushButton>

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
    std::cout << e.dist_origin() << std::endl;
    return app.exec();
}