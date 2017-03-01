//
// Created by kev on 01/03/17.
//

#ifndef DRAWSHEEP_WINDOW_HPP
#define DRAWSHEEP_WINDOW_HPP
#include <iostream>
#include <Shape.hpp>
#include <Ellipse.hpp>
#include <Circle.hpp>
#include <Polygon.hpp>
#include <Line.hpp>
#include <QMainWindow>
#include <QApplication>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>

class Window : public QMainWindow
{

public:
    Window();
    ~Window();

    void mouseReleaseEvent(QMouseEvent *event);

private:
    std::vector<Point> queue_point;
    QPushButton *m_button_quit;
    int type_figure = 0;
    std::vector<Shape *> list_figure;
};

#endif //DRAWSHEEP_WINDOW_HPP
