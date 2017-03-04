//
// Created by kev on 01/03/17.
//


#include <Window.hpp>
#include <QColorDialog>

Window::Window(){
    scene = new QGraphicsScene(this);
    setFixedSize(1500,900);
    this->setScene(scene);

    //création d'une ligne diagonale transparente pour éviter le recadrage de la fenetre
    QPen pen(Qt::transparent);
    QLineF line(0,0,1500,900);
    scene->addLine(line,pen);

    m_button_quit = new QPushButton("Quittez",this);
    m_button_selection = new QPushButton("Selection",this);
    m_button_line = new QPushButton("Ligne",this);
    m_button_ellipse = new QPushButton("Ellipse",this);
    m_button_polygon = new QPushButton("Polygone",this);
    m_button_fin_polygon = new QPushButton("Fin Polygone",this);
    m_button_color_background = new QPushButton("Couleur interne",this);
    m_button_color_contour = new QPushButton("Couleur contour",this);
    m_button_move = new QPushButton("Deplacer",this);
    m_button_scale = new QPushButton("Agrandir/Reduire",this);
    m_button_rotate = new QPushButton("Rotation",this);
    m_button_axial_sym = new QPushButton("Symetrie Axiale",this);
    m_button_central_sym = new QPushButton("Symetrie Centrale",this);

    m_button_quit->setToolTip("quittez l'application");
    m_button_selection->setToolTip("selectionner une figure pour lui appliquer des modifications");
    m_button_line->setToolTip("creer une ligne");
    m_button_ellipse->setToolTip("creer une ellipse");
    m_button_polygon->setToolTip("creer un polygone");
    m_button_fin_polygon->setToolTip("mettre fin a l'ajout de point pour la creation du polygone");
    m_button_color_background->setToolTip("changer la couleur du fond de la figure");
    m_button_color_contour->setToolTip("changer la couleur du contour de la figure");
    m_button_move->setToolTip("deplacer la figure");
    m_button_scale->setToolTip("agrandir ou reduire la figure");
    m_button_rotate->setToolTip("rotationner la figure");
    m_button_axial_sym->setToolTip("appliquer une symetrie axiale a la figure depuis le point clique");
    m_button_central_sym->setToolTip("appliquer une symétrie centrale a la figure depuis la ligne creee");

    m_button_quit->setFixedSize(100, 25);
    m_button_selection->setFixedSize(100, 25);
    m_button_line->setFixedSize(100, 25);
    m_button_ellipse->setFixedSize(100, 25);
    m_button_polygon->setFixedSize(100, 25);
    m_button_fin_polygon->setFixedSize(100, 25);
    m_button_color_background->setFixedSize(150, 25);
    m_button_color_contour->setFixedSize(150, 25);
    m_button_move->setFixedSize(100, 25);
    m_button_scale->setFixedSize(150, 25);
    m_button_rotate->setFixedSize(100, 25);
    m_button_axial_sym->setFixedSize(150, 25);
    m_button_central_sym->setFixedSize(150, 25);

    m_button_selection->move(0,25);
    m_button_line->move(0,50);
    m_button_ellipse->move(0,75);
    m_button_polygon->move(0,100);
    m_button_fin_polygon->move(0,125);
    m_button_color_background->move(100,0);
    m_button_color_contour->move(100,25);
    m_button_move->move(100,50);
    m_button_scale->move(100,75);
    m_button_rotate->move(100,100);
    m_button_axial_sym->move(100,125);
    m_button_central_sym->move(100,150);

//    la souris montre que le bouton est cliquable
    m_button_quit->setCursor(Qt::PointingHandCursor);
    m_button_selection->setCursor(Qt::PointingHandCursor);
    m_button_line->setCursor(Qt::PointingHandCursor);
    m_button_ellipse->setCursor(Qt::PointingHandCursor);
    m_button_polygon->setCursor(Qt::PointingHandCursor);
    m_button_fin_polygon->setCursor(Qt::PointingHandCursor);
    m_button_color_background->setCursor(Qt::PointingHandCursor);
    m_button_color_contour->setCursor(Qt::PointingHandCursor);
    m_button_move->setCursor(Qt::PointingHandCursor);
    m_button_scale->setCursor(Qt::PointingHandCursor);
    m_button_rotate->setCursor(Qt::PointingHandCursor);
    m_button_axial_sym->setCursor(Qt::PointingHandCursor);
    m_button_central_sym->setCursor(Qt::PointingHandCursor);


    //les buttons n'apparaisse que si l'on a selectionner une figure
    disable_buttons();

//    quand on clique sur le bouton on quitte l'appli
    QObject::connect(m_button_quit,SIGNAL(clicked()),qApp,SLOT(quit()));
    QObject::connect(m_button_selection,SIGNAL(clicked()),this,SLOT(button_selection()));
    QObject::connect(m_button_line,SIGNAL(clicked()),this,SLOT(button_line()));
    QObject::connect(m_button_ellipse,SIGNAL(clicked()),this,SLOT(button_ellipse()));
    QObject::connect(m_button_polygon,SIGNAL(clicked()),this,SLOT(button_polygon()));
    QObject::connect(m_button_fin_polygon,SIGNAL(clicked()),this,SLOT(button_fin_polygon()));
    QObject::connect(m_button_color_background,SIGNAL(clicked()),this,SLOT(button_color_background()));
    QObject::connect(m_button_color_contour,SIGNAL(clicked()),this,SLOT(button_color_contour()));
    QObject::connect(m_button_move,SIGNAL(clicked()),this,SLOT(button_move()));
    QObject::connect(m_button_scale,SIGNAL(clicked()),this,SLOT(button_scale()));
    QObject::connect(m_button_rotate,SIGNAL(clicked()),this,SLOT(button_rotate()));
    QObject::connect(m_button_axial_sym,SIGNAL(clicked()),this,SLOT(button_axial_sym()));
    QObject::connect(m_button_central_sym,SIGNAL(clicked()),this,SLOT(button_central_sym()));

}

Window::~Window(){}

void Window::enable_buttons() {
    m_button_color_background->setDisabled(false);
    m_button_color_contour->setDisabled(false);
    m_button_move->setDisabled(false);
    m_button_scale->setDisabled(false);
    m_button_rotate->setDisabled(false);
    m_button_axial_sym->setDisabled(false);
    m_button_central_sym->setDisabled(false);
}

void Window::disable_buttons() {
    m_button_color_background->setDisabled(true);
    m_button_color_contour->setDisabled(true);
    m_button_move->setDisabled(true);
    m_button_scale->setDisabled(true);
    m_button_rotate->setDisabled(true);
    m_button_axial_sym->setDisabled(true);
    m_button_central_sym->setDisabled(true);
}

void Window::button_selection() {
    disable_buttons();
    if(type_button == 2){
        button_fin_polygon();
    }
    type_button = 3;
}

void Window::button_line() {
    disable_buttons();
    if(type_button == 2){
        button_fin_polygon();
    }
    type_button = 0;
}

void Window::button_ellipse() {
    disable_buttons();
    if(type_button == 2){
        button_fin_polygon();
    }
    type_button = 1;
}

void Window::button_polygon() {
    disable_buttons();
    type_button = 2;
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

void Window::button_color_background() {
    QColor color = QColorDialog::getColor(Qt::white,this);
    QPalette pal;
    pal.setColor(QPalette::Background,color);
    //modif tmpitem background
}

void Window::button_color_contour() {
    QColor color = QColorDialog::getColor(Qt::white,this);
    QPalette pal;
    pal.setColor(QPalette::Background,color);
    //modif tmpitem contour
}

void Window::button_move() {

}

void Window::button_scale() {

}

void Window::button_rotate() {

}

void Window::button_axial_sym() {

}

void Window::button_central_sym() {

}

//permet d'appliquer la fonction mooveEvent quand la souris bouge
//et créer un prototype de la figure jusquau relachement de la souris
void Window::mousePressEvent(QMouseEvent *event) {
    figure_on_creation = true;
    int actual_x = event->pos().x();
    int actual_y = event->pos().y();
    if(type_button != 2 || list_line_polygon.size() == 0){
        tmp_point = Point(actual_x,actual_y);
        queue_point.push_back(tmp_point);
    }
    switch(type_button) {
        case 0:
            //line
            tmp_line = new QGraphicsLineItem(QLineF(QPointF(actual_x,actual_y),QPointF(actual_x,actual_y)));
            scene->addItem(tmp_line);
            break;
        case 1:
            //ellipse
            tmp_ellipse = new QGraphicsEllipseItem(actual_x,actual_y,0,0);
            scene->addItem(tmp_ellipse);
            break;
        case 2:
            //polygon
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
        switch(type_button) {
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
        if(type_button != 2){
            queue_point.push_back(Point(event->pos().x(),event->pos().y()));
        }

        //affichage du point
        //scene->addLine(event->pos().x(),event->pos().y(),event->pos().x(),event->pos().y());
        //std::cout << event->pos().x() << " " << event->pos().y() << std::endl;

        switch(type_button){
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
                break;
            }
            case 3:
            {
                tmp_item_modified = itemAt(event->pos());
                if(tmp_item_modified != nullptr){
                    enable_buttons();
                }
                break;
            }
            default:
                break;
            //polygone se fais a part, lorsqu'on clique sur le bouton fermer polygone il se créer.
        }
    }
}

