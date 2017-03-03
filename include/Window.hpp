//
// Created by kev on 01/03/17.
//

#ifndef DRAWSHEEP_WINDOW_HPP
#define DRAWSHEEP_WINDOW_HPP
#include <iostream>
#include <My_Shape.hpp>
#include <Ellipse.hpp>
#include <Circle.hpp>
#include <Polygon.hpp>
#include <Line.hpp>
#include <QApplication>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsLineItem>
#include <QObject>

class Window : public QGraphicsView
{
//    Q_OBJECT
//public slot:
//    void testQuit();
public:
    Window();
    ~Window();

    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void button_selection();
    void button_line();
    void button_ellipse();
    void button_polygon();
    void button_fin_polygon();

private:
    QGraphicsScene *scene;
    std::vector<Point> queue_point;
    std::vector<My_Shape *> list_figure;
    Point tmp_point;
    QGraphicsLineItem *tmp_line = nullptr;
    QGraphicsEllipseItem *tmp_ellipse = nullptr;
    QGraphicsPolygonItem *tmp_polygon = nullptr;
    std::vector<QGraphicsLineItem *> list_line_polygon;
    QPushButton *m_button_quit;
    int type_figure = 2;
    bool figure_on_creation = false;
};

#endif //DRAWSHEEP_WINDOW_HPP
