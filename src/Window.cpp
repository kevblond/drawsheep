//
// Created by kev on 01/03/17.
//


#include <Window.hpp>

Window::Window(){
    scene = new QGraphicsScene(this);
    setFixedSize(1500,900);
    this->setScene(scene);
//    m_button_quit = new QPushButton("Quittez",this);
//    m_button_quit->setToolTip("quittez l'application");
//    m_button_quit->setFixedSize(100, 100);
////    la souris montre que le bouton est cliquable
//    m_button_quit->setCursor(Qt::PointingHandCursor);
////    quand on clique sur le bouton on quitte l'appli
//    QObject::connect(m_button_quit,SIGNAL(clicked()),qApp,SLOT(quit()));
}

Window::~Window(){

}

void Window::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        queue_point.push_back(Point(event->pos().x(),event->pos().y()));
        std::cout << event->pos().x() << " " << event->pos().y() << std::endl;
        switch(type_figure){
            case 0:
                //line
                if(queue_point.size() == 2){
                    std::cout << "create line "<< std::endl;
                    Point A = queue_point[0];
                    Point B = queue_point[1];
                    list_figure.push_back(new Line(A,B));
                    QLineF qf(A.get_x(),A.get_y(),B.get_x(),B.get_y());
                    std::cout << qf.x1() << " " << qf.y1() << " " << qf.x2() << " " << qf.y2() << std::endl;
                    scene->addLine(qf);
                    std::cout << scene->items().size() << std::endl;
                    queue_point.clear();
                }
                break;
            case 1:
                //cercle
                if(queue_point.size() == 2){
                    Point O = queue_point[0];
                    Point T = queue_point[1];
                    list_figure.push_back(new Circle(O,distance(O,T)));
                    scene->addEllipse(O.get_x(),O.get_y(),distance(O,T),distance(O,T));
                    queue_point.clear();
                }
                break;
            case 2:
                //ellipse
                if(queue_point.size() == 3){
                    Point O = queue_point[0];
                    Point A = queue_point[1];
                    Point B = queue_point[2];
                    list_figure.push_back(new Ellipse(O,distance(O,A),distance(O,B)));
                    scene->addEllipse(O.get_x(),O.get_y(),distance(O,A),distance(O,B));
                    queue_point.clear();
                }

                break;
            //polygone se fais a part, lorsqu'on clique sur le bouton fermer polygone il se créer.
        }
    }
}

