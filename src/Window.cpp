//
// Created by kev on 01/03/17.
//


#include <Window.hpp>

Window::Window(){
    scene = new QGraphicsScene(this);
    setFixedSize(1500,900);
    this->setScene(scene);

    //création d'une ligne diagonale transparente pour éviter le recadrage de la fenetre
    QPen pen(Qt::transparent);
    QLineF line(0,0,1500,900);
    scene->addLine(line,pen);

    m_button_quit = new QPushButton("Quittez",this);
    m_button_quit->setToolTip("quittez l'application");
    m_button_quit->setFixedSize(100, 25);
//    la souris montre que le bouton est cliquable
    m_button_quit->setCursor(Qt::PointingHandCursor);
//    quand on clique sur le bouton on quitte l'appli
    QObject::connect(m_button_quit,SIGNAL(clicked()),this,SLOT(testQuit()));
}

Window::~Window(){}

void Window::testQuit() {
    exit(EXIT_SUCCESS);
}

void Window::button_line() {
    type_figure = 0;
}

void Window::button_ellipse() {
    type_figure = 1;
}

void Window::button_polygon() {
    type_figure = 2;
}

//supprime les lignes affichées temporairement et créer le polygon final.
void Window::button_fin_polygon() {
    QVector<QPointF> v;
    for(Point p:queue_point){
        v.push_back(QPointF(p.get_x(),p.get_y()));
    }
    QPolygonF pol = QPolygonF(v);
    for(QGraphicsLineItem *line : list_line_polygon){
        scene->removeItem(line);
    }
    scene->addPolygon(pol);
    tmp_line = nullptr;
    list_line_polygon.clear();
    queue_point.clear();
}

//permet d'appliquer la fonction mooveEvent quand la souris bouge
//et créer un prototype de la figure jusquau relachement de la souris
void Window::mousePressEvent(QMouseEvent *event) {
    //peut etre empeché le press si lemplacement se trouve sur les boutons
    figure_on_creation = true;
    int actual_x = event->pos().x();
    int actual_y = event->pos().y();
    if(type_figure != 2 || list_line_polygon.size() == 0){
        tmp_point = Point(actual_x,actual_y);
        queue_point.push_back(tmp_point);
    }
    switch(type_figure) {
        case 0:
            //line
            std::cout << "create line " << std::endl;
            tmp_line = new QGraphicsLineItem(QLineF(QPointF(actual_x,actual_y),QPointF(actual_x,actual_y)));
            scene->addItem(tmp_line);
            break;
        case 1:
            //ellipse
            std::cout << "create ellipse " << std::endl;
            tmp_ellipse = new QGraphicsEllipseItem(actual_x,actual_y,0,0);
            scene->addItem(tmp_ellipse);
            break;
        case 2:
            //polygon
            std::cout << "create polygon "<<std::endl;
            tmp_line = new QGraphicsLineItem(QLineF(QPointF(tmp_point.get_x(),tmp_point.get_y()),QPointF(actual_x,actual_y)));
            scene->addItem(tmp_line);
            break;
        default:
            break;
    }
}

//modifie le prototype de la figure jusqu'au relachement de la souris
void Window::mouseMoveEvent(QMouseEvent *event) {
    if(figure_on_creation){
        int actual_x = event->pos().x();
        int actual_y = event->pos().y();
        switch(type_figure) {
            case 0:
                //line
                scene->removeItem(tmp_line);
                tmp_line = new QGraphicsLineItem(QLineF(QPointF(tmp_point.get_x(),tmp_point.get_y()),QPointF(actual_x,actual_y)));
                scene->addItem(tmp_line);
                break;
            case 1:
            {
                //ellipse
                //decoupé en 4 la creation de lellipse
                scene->removeItem(tmp_ellipse);
                float OTX = fabsf(actual_x - tmp_point.get_x());
                float OTY = fabsf(actual_y - tmp_point.get_y());
                Point tmp = tmp_point;
                //4 direction de la souris entre press et release
                if(tmp_point.get_x() < actual_x){
                    if(tmp_point.get_y() < actual_y){
                        //bas à droite
                        //comportement normal donc vide
                    }
                    else{
                    //haut à droite
                    tmp = Point(tmp_point.get_x(), tmp_point.get_y() - OTY);
                    }
                }
                else{
                    if(tmp_point.get_y() < actual_y){
                        //bas à gauche
                        tmp = Point(tmp_point.get_x() - OTX, tmp_point.get_y());
                    }
                    else{
                        //haut à gauche
                        tmp = Point(tmp_point.get_x() - OTX, tmp_point.get_y() - OTY);
                    }
                }
                tmp_ellipse = new QGraphicsEllipseItem(tmp.get_x(),tmp.get_y(),OTX,OTY);
                scene->addItem(tmp_ellipse);
                break;
            }
            case 2:
                //polygon
                scene->removeItem(tmp_line);
                tmp_line = new QGraphicsLineItem(QLineF(QPointF(tmp_point.get_x(),tmp_point.get_y()),QPointF(actual_x,actual_y)));
                scene->addItem(tmp_line);
                break;
            default:
                break;
        }
    }
}

//créer la forme dessiné
void Window::mouseReleaseEvent(QMouseEvent *event){

    figure_on_creation = false;

    if(event->button() == Qt::LeftButton){
        if(type_figure != 2){
            queue_point.push_back(Point(event->pos().x(),event->pos().y()));
        }

        //affichage du point
        //scene->addLine(event->pos().x(),event->pos().y(),event->pos().x(),event->pos().y());
        //std::cout << event->pos().x() << " " << event->pos().y() << std::endl;

        switch(type_figure){
            case 0:
            {
                //line
                scene->removeItem(tmp_line);
                tmp_line = nullptr;
                std::cout << "create line "<< std::endl;
                Point A = queue_point[0];
                Point B = queue_point[1];
                list_figure.push_back(new Line(A,B));

                QPointF Af = mapToScene(static_cast<int>(A.get_x()),static_cast<int>(A.get_y()));
                QPointF Bf = mapToScene(static_cast<int>(B.get_x()),static_cast<int>(B.get_y()));

                scene->addLine(QLineF(Af,Bf));

                queue_point.clear();
                break;
            }

            case 1:
            {
                //ellipse
                //decoupé en 4 la creation de lellipse
                scene->removeItem(tmp_ellipse);
                tmp_ellipse = nullptr;
                std::cout << "create ellipse " << std::endl;
                Point O = queue_point[0];
                Point T = queue_point[1];
                float OTX = fabsf(T.get_x() - O.get_x());
                float OTY = fabsf(T.get_y() - O.get_y());
                //4 direction de la souris entre press et release
                if(O.get_x() < T.get_x()){
                    if(O.get_y() < T.get_y()){
                        //bas à droite
                        //comportement normal donc vide
                    }
                    else{
                    //haut à droite
                    O = Point(O.get_x(), O.get_y() - OTY);
                    }
                }
                else{
                    if(O.get_y() < T.get_y()){
                        //bas à gauche
                        O = Point(O.get_x() - OTX, O.get_y());
                    }
                    else{
                        //haut à gauche
                        O = Point(O.get_x() - OTX, O.get_y() - OTY);
                    }
                }
                Point center(O.get_x()+OTX/2,O.get_y()+OTY/2);
                list_figure.push_back(new Ellipse(center,fabsf(OTX),fabsf(OTY)));
                scene->addEllipse(O.get_x(),O.get_y(),fabsf(OTX),fabsf(OTY));

                queue_point.clear();
                break;
            }

            case 2:
            {
                //line
                scene->removeItem(tmp_line);
                std::cout << "create polygon "<< std::endl;
                Point A = tmp_point;
                Point B = Point(event->pos().x(),event->pos().y());
                queue_point.push_back(B);

                QPointF Af = mapToScene(static_cast<int>(A.get_x()),static_cast<int>(A.get_y()));
                QPointF Bf = mapToScene(static_cast<int>(B.get_x()),static_cast<int>(B.get_y()));

                tmp_line = new QGraphicsLineItem(QLineF(QPointF(Af.x(),Af.y()),QPointF(Bf.x(),Bf.y())));
                scene->addItem(tmp_line);
                list_line_polygon.push_back(tmp_line);
                tmp_line = nullptr;

                tmp_point = Point(event->pos().x(),event->pos().y());
//                if(queue_point.size() == 5){
//                    button_fin_polygon();
//                }
                break;
            }
            default:
                break;
            //polygone se fais a part, lorsqu'on clique sur le bouton fermer polygone il se créer.
        }
    }
}

