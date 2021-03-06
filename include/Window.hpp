//
// Created by kev on 01/03/17.
//

#ifndef DRAWSHEEP_WINDOW_HPP
#define DRAWSHEEP_WINDOW_HPP
#include <My_Shape.hpp>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QObject>
#include <Client.hpp>

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
    void button_save();
    void button_delete();

public:
    Window();
    ~Window();

    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);



private:
    QGraphicsScene *scene;
    Client *client;


    std::vector<Point> queue_point;
    std::vector<std::pair<My_Shape *,QGraphicsItem *>> list_figure;

    Point tmp_point;
    QGraphicsLineItem *tmp_line = nullptr;
    QGraphicsEllipseItem *tmp_ellipse = nullptr;
    QGraphicsPolygonItem *tmp_polygon = nullptr;
    std::vector<QGraphicsLineItem *> list_line_polygon;

    std::pair<My_Shape*,QGraphicsItem*> tmp_item_modified;
    int type_item_modified = -1;

    float tmp_angle_rotation = 0;

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
    QPushButton *m_button_save;
    QPushButton *m_button_delete;

    //bouton de selection par defaut
    int type_button = 3;
    bool figure_on_creation = false;

    void move_and_add_tmp_item(float actual_x, float actual_y);
    void scale_and_add_tmp_item(float actual_x, float actual_y);
    void rotate_and_add_tmp_item(float actual_x, float actual_y);
    void enable_buttons();
    void disable_buttons();
    void clear_action();

    void delete_figure_before_modif();
};

#endif //DRAWSHEEP_WINDOW_HPP
