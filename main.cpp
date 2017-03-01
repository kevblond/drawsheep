#include <iostream>
#include <Shape.hpp>
#include <Ellipse.hpp>
#include <Polygon.hpp>
#include <QApplication>
#include <QPushButton>
#include <Line.hpp>
#include <Window.hpp>
#include <QGraphicsScene>
#include <QGraphicsView>

// TODO Faire des tests unitaires, rapporte des points dans le rapport

int main(int argc, char **argv) {
    QApplication app(argc, argv);

//    QPushButton drawing("Quittez",&fenetre);
//
//    drawing.setToolTip("ce message s'affiche quand on passe la souris sur le drawing");
//    drawing.setFixedSize(100, 100);
//    la souris montre que le bouton est cliquable
//    drawing.setCursor(Qt::PointingHandCursor);
//    quand on clique sur le bouton on quitte l'appli
//    QObject::connect(&drawing,SIGNAL(clicked()),qApp,SLOT(quit()));
//    QObject::connect(&fenetre,SIGNAL(clicked()),qApp,SLOT(create_point()));

    QGraphicsScene scene;
    //line
    scene.addLine(QLineF(10,10,1400,700));
    //ellipse
    scene.addEllipse(500,500,50,100);
    //circle
    scene.addEllipse(700,700,50,50);
    //polygone
    QVector<QPointF> v;
    v.push_back(QPointF(120,30));
    v.push_back(QPointF(50,80));
    v.push_back(QPointF(0,20));
    v.push_back(QPointF(20,0));
    scene.addPolygon(QPolygonF(v));
    QGraphicsView view(&scene);

    view.setFixedSize(1400,900);
    view.show();

//    Window fenetre;
//    fenetre.show();

    Point p(3,3);

    Line l(Point(0,2),Point(2,0));

    float rx = 2;
    float ry = 2;
    Ellipse e(p,rx,ry);

    std::vector<Point> polyPoint;
    polyPoint.push_back(Point(12,3));
    polyPoint.push_back(Point(5,8));
    polyPoint.push_back(Point(0,2));
    polyPoint.push_back(Point(2,0));
    Polygon pol(polyPoint);

//    pol.rotate(5);
//    Point o;
//    p.central_sym(o);
//    pol.central_sym(o);
//    l.central_sym(o);
//    e.central_sym(o);

    Point o1(10,10);
    Point o2(11,9);
    p.axial_sym(o1,o2);
    std::cout << pol.gravity_center() << std::endl;
    pol.axial_sym(o1,o2);
    l.axial_sym(o1,o2);
    e.axial_sym(o1,o2);
//    std::cout << p << std::endl;
    std::cout << pol.gravity_center() << std::endl;
//    std::cout << l.milieu_segment() << std::endl;

    return app.exec();
//    return 0;
}