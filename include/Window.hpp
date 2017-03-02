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
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>

class Window : public QGraphicsView
{

public:
    Window();
    ~Window();

    void mouseReleaseEvent(QMouseEvent *event);

private:
    QGraphicsScene *scene;

    std::vector<Point> queue_point;
    std::vector<My_Shape *> list_figure;
    QPushButton *m_button_quit;
    int type_figure = 0;
};

#endif //DRAWSHEEP_WINDOW_HPP
