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
    Q_OBJECT
public slots:
    void button_line();
    void button_ellipse();
    void button_polygon();
    void button_fin_polygon();
    void button_selection();
    void button_color_background();
    void button_color_contour();
    void button_move();
    void button_scale();
    void button_rotate();
    void button_axial_sym();
    void button_central_sym();

public:
    Window();
    ~Window();

    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void enable_buttons();
    void disable_buttons();
    void clear_action();

    void delete_figure_before_modif();


private:
    QGraphicsScene *scene;

    std::vector<Point> queue_point;
    std::vector<std::pair<My_Shape *,QGraphicsItem *>> list_figure;

    Point tmp_point;
    QGraphicsLineItem *tmp_line = nullptr;
    QGraphicsEllipseItem *tmp_ellipse = nullptr;
    QGraphicsPolygonItem *tmp_polygon = nullptr;
    std::vector<QGraphicsLineItem *> list_line_polygon;

    std::pair<My_Shape*,QGraphicsItem*> tmp_item_modified;
    int type_item_modified = -1;

    QPushButton *m_button_quit;
    QPushButton *m_button_line;
    QPushButton *m_button_ellipse;
    QPushButton *m_button_polygon;
    QPushButton *m_button_fin_polygon;
    QPushButton *m_button_selection;
    QPushButton *m_button_color_background;
    QPushButton *m_button_color_contour;
    QPushButton *m_button_move;
    QPushButton *m_button_scale;
    QPushButton *m_button_rotate;
    QPushButton *m_button_axial_sym;
    QPushButton *m_button_central_sym;

    int type_button = 6;
    bool figure_on_creation = false;
};

#endif //DRAWSHEEP_WINDOW_HPP
