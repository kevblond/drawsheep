//
// Created by kev on 01/03/17.
//


#include <Window.hpp>
#include <QColorDialog>
#include <QInputDialog>
#include <QApplication>
#include <Polygon.hpp>
#include <Ellipse.hpp>
#include <Line.hpp>

///constructeur de la fenêtre utilisateur
Window::Window(){
    scene = new QGraphicsScene(this);
    setFixedSize(1500,900);
    this->setScene(scene);

    bool ok;
    QString text = QInputDialog::getText(this, tr("Connexion au server"),
                                         tr("nom / Ip serveur:"), QLineEdit::Normal,
                                         "localhost", &ok);
    if (ok && !text.isEmpty()) {
        client = new Client(text.toStdString().c_str(), 20000);
    }

    //création d'une ligne diagonale transparente pour éviter le recadrage de la fenetre
    QPen pen(Qt::transparent);
    QLineF line(0,0,1500,900);
    QGraphicsLineItem *l = new QGraphicsLineItem(line);
    l->setVisible(false);
    scene->addItem(l);

    //initialisation de l'item de selection
    tmp_item_modified.first = nullptr;
    tmp_item_modified.second = nullptr;

    //initialisation des boutons
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
    m_button_save = new QPushButton("Sauvegarder", this);
    m_button_delete = new QPushButton("Supprimer", this);

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
    m_button_save->setToolTip("sauvegarder et envoyer au serveur");
    m_button_delete->setToolTip("supprimer la figure selectionnée");

    //taille
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
    m_button_save->setFixedSize(100, 25);
    m_button_delete->setFixedSize(100,25);

    //placement
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
    m_button_save->move(0,150);
    m_button_delete->move(100,175);

    //la souris montre que le bouton est cliquable
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
    m_button_save->setCursor(Qt::PointingHandCursor);
    m_button_delete->setCursor(Qt::PointingHandCursor);

    //les buttons de modification n'apparaissent que si l'on a selectionné une figure
    disable_buttons();

    //assocation des boutons avec leur fonction respective
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
    QObject::connect(m_button_save,SIGNAL(clicked()),this,SLOT(button_save()));
    QObject::connect(m_button_delete,SIGNAL(clicked()),this,SLOT(button_delete()));
}

Window::~Window(){}

///dégriser les boutons de modifications
void Window::enable_buttons() {
    m_button_color_background->setDisabled(false);
    m_button_color_contour->setDisabled(false);
    m_button_move->setDisabled(false);
    m_button_scale->setDisabled(false);
    m_button_rotate->setDisabled(false);
    m_button_axial_sym->setDisabled(false);
    m_button_central_sym->setDisabled(false);
    m_button_delete->setDisabled(false);
}

///griser les boutons de modifications
void Window::disable_buttons() {
    m_button_color_background->setDisabled(true);
    m_button_color_contour->setDisabled(true);
    m_button_move->setDisabled(true);
    m_button_scale->setDisabled(true);
    m_button_rotate->setDisabled(true);
    m_button_axial_sym->setDisabled(true);
    m_button_central_sym->setDisabled(true);
    m_button_delete->setDisabled(true);
    //disable ce bouton et enable que lors de la creation d'un polygone
    m_button_fin_polygon->setDisabled(true);
}

///passage d'un boutons à un autre en nettoyant les valeurs
void Window::clear_action(){
    disable_buttons();
    if(type_button == 5){
        button_fin_polygon();
    }
    tmp_line = nullptr;
    type_item_modified = -1;
    tmp_item_modified.first = nullptr;
    tmp_item_modified.second = nullptr;
    list_line_polygon.clear();
    queue_point.clear();
}

///slot du boutton de selection
void Window::button_selection() {
    clear_action();
    type_button = 3;
}

///slot du boutton de création de ligne
void Window::button_line() {
    clear_action();
    type_button = 6;
}

///slot du boutton de création d'ellipse
void Window::button_ellipse() {
    clear_action();
    type_button = 4;
}

///slot du boutton de création de polygone
void Window::button_polygon() {
    clear_action();
    //afficher fin polygon seulement si on créer un polygone
    m_button_fin_polygon->setDisabled(false);
    type_button = 5;
}

///supprime les lignes affichées temporairement et créer le polygone final
void Window::button_fin_polygon() {
    std::cout << "create polygon" << std::endl;
    //si le polygone en cours de création n'a que 2 point on ne peux pas finir ce polygone
    if(queue_point.size() >= 3){
        QVector<QPointF> v;
        std::vector<Point> v2;
        for(Point p:queue_point){
            v.push_back(QPointF(p.get_x(),p.get_y()));
            v2.push_back(Point(p.get_x(),p.get_y()));
        }
        QPolygonF pol = QPolygonF(v);
        QGraphicsPolygonItem *polygon = new QGraphicsPolygonItem(pol);
        scene->addItem(polygon);

        std::pair<My_Shape *,QGraphicsItem *> p;
        p.first = new Polygon(v2);
        p.second = polygon;
        list_figure.push_back(p);
    }

    //nettoie les lignes affiché pour représenter le polygone avant sa création
    for(QGraphicsLineItem *line : list_line_polygon){
        scene->removeItem(line);
    }
    tmp_line = nullptr;
    list_line_polygon.clear();
    queue_point.clear();
}

///slot du boutton de coloration interne de la figure selectionnée
void Window::button_color_background() {
    delete_figure_before_modif();
    QPen pen;
    QColor color_background = QColorDialog::getColor(Qt::white,this);
    switch(type_item_modified){
        case 4:
            //ellipse
            tmp_item_modified.first->setBrush(color_background);
            ((QGraphicsEllipseItem *) tmp_item_modified.second )->setBrush(QBrush(color_background));
            break;
        case 5:
            //polygon
            tmp_item_modified.first->setBrush(color_background);
            ((QGraphicsPolygonItem *) tmp_item_modified.second )->setBrush(QBrush(color_background));
            break;
        case 6:
            //line
            //pas de remplissage d'une ligne
            break;
        default:
            break;
    }
    scene->addItem(tmp_item_modified.second);
    list_figure.push_back(tmp_item_modified);
    //modif tmpitem background
}

///slot du boutton de coloration du contour de la figure séléctionnée
void Window::button_color_contour() {
    delete_figure_before_modif();
    QColor color_contour = QColorDialog::getColor(Qt::white,this);
    QPen pen;

    pen.setBrush(Qt::NoBrush);
    pen.setColor(color_contour);

    //type lors de la selection
    switch(type_item_modified){
        case 4:
            //ellipse
            tmp_item_modified.first->setPen(pen);
            ((QGraphicsEllipseItem *)tmp_item_modified.second)->setPen(pen);
            break;
        case 5:
            //polygon
            tmp_item_modified.first->setPen(pen);
            ((QGraphicsPolygonItem *)tmp_item_modified.second)->setPen(pen);
            break;
        case 6:
            //line
            tmp_item_modified.first->setPen(pen);
            ((QGraphicsLineItem *)tmp_item_modified.second)->setPen(pen);
            break;
        default:
            break;
    }
    scene->addItem(tmp_item_modified.second);
    list_figure.push_back(tmp_item_modified);
}

///slot du boutton de déplacement de la figure selectionnée
void Window::button_move() {
    type_button = 7;
}

///slot du boutton d'agrandissement/rétrecissement de la figure selectionnée
void Window::button_scale() {
    type_button = 8;
}

///slot du boutton de rotation de la figure selectionnée
void Window::button_rotate() {
    type_button = 9;
}

///slot du boutton de symétrie axiale de la figure selectionnée
void Window::button_axial_sym() {
    type_button = 10;
}

///slot du boutton de symétrie centrale de la figure selectionnée
void Window::button_central_sym() {
    type_button = 11;
}

///slot du boutton de sauvegarde du dessin
void Window::button_save() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Sauvegarder et envoyer au serveur"),
                                         tr("Nom du fichier:"), QLineEdit::Normal,
                                         "save.txt", &ok);
    if (ok && !text.isEmpty()) {
        for (std::pair<My_Shape *, QGraphicsItem*> shape : list_figure) {
            My_Shape *my_shape = shape.first;
            my_shape->save_to_file(text.toStdString().c_str());
        }
    }

    try {
        client->send_file(text.toStdString().c_str());
    } catch (const char *err){
        std::cerr << err << std::endl;
        return;
    }
}

///slot du boutton de suppression de la figure selectionnée
void Window::button_delete() {
    delete_figure_before_modif();
    clear_action();
    type_button = 3;
}

/**
 * suppression de la figure selectionnée
 * utilisé pendant le clic de souris pour supprimé l'ancienne figure avant de créer la nouvelle
 * mais aussi pour supprimer définitivement avec le boutton supprimer
 */
void Window::delete_figure_before_modif(){
    scene->removeItem(tmp_item_modified.second);
    //supprime la valeur sauvegarder pour la remettre après le release
    for(std::vector<std::pair<My_Shape*,QGraphicsItem*>>::iterator i = list_figure.begin(); i < list_figure.end(); i++){
        if(i->second == tmp_item_modified.second){
            list_figure.erase(i);
        }
    }
}

/**
 *  déplace et ajoute un item provisoire à la vue
 *  utilisé lors du déplacement de souris en restant appuyé
 * @param actual_x position x de la souris
 * @param actual_y position y de la souris
 */
void Window::move_and_add_tmp_item(float actual_x,float actual_y) {
    float trans_x = actual_x - tmp_point.get_x();
    float trans_y = actual_y - tmp_point.get_y();
    tmp_point += Point(trans_x,trans_y);
    tmp_item_modified.first->translate(trans_x,trans_y);
    tmp_item_modified.second = tmp_item_modified.first->getItem();
    scene->addItem(tmp_item_modified.second);
}

/**
 * agrandis et ajoute un item provisoire à la vue
 * utilisé lors du déplacement de souris en restant appuyé
 * @param actual_x position x de la souris
 * @param actual_y position y de la souris
 */
void Window::scale_and_add_tmp_item(float actual_x, float actual_y) {
    float dist_point = distance(Point(actual_x,actual_y),tmp_point);
    float scale = dist_point / tmp_item_modified.first->ref_scale();
    //eviter de faire disparaitre la figure
    if(scale == 0){
        scale = 0.01;
    }
    if(type_item_modified == 6){
        ((Line*)tmp_item_modified.first)->scale_line(actual_x,actual_y);
    }
    else{
        tmp_item_modified.first->scale(scale);
    }
    tmp_item_modified.second = tmp_item_modified.first->getItem();
    scene->addItem(tmp_item_modified.second);
}

/**
 * rotationne et ajoute un item provisoire à la vue
 * utilisé lors du déplacement de souris en restant appuyé
 * @param actual_x position x de la souris
 * @param actual_y position y de la souris
 */
void Window::rotate_and_add_tmp_item(float actual_x, float actual_y) {
    Point t;
    Point p_mouse(actual_x,actual_y);
    float angle = 0;
    if(distance(tmp_point,p_mouse) != 0){
        if(actual_x < tmp_point.get_x()){
            if(actual_y < tmp_point.get_y()){
                t = Line(tmp_point,Point(tmp_point.get_x(),tmp_point.get_y()+1)).projete_orthog(p_mouse);
                float adj_hyp = distance(tmp_point,t)/distance(tmp_point,p_mouse);
                adj_hyp = adj_hyp > 1 ? 1 : adj_hyp;
                angle = (float)(M_PI/2+acosf(adj_hyp));
            }
            else{
                t = Line(tmp_point,Point(tmp_point.get_x()-1,tmp_point.get_y())).projete_orthog(p_mouse);
                float adj_hyp = distance(tmp_point,t)/distance(tmp_point,p_mouse);
                adj_hyp = adj_hyp > 1 ? 1 : adj_hyp;
                angle = (float)(M_PI + acosf(adj_hyp));
            }
        }
        else{
            t = Line(tmp_point,Point(tmp_point.get_x()+1,tmp_point.get_y())).projete_orthog(p_mouse);
            if(actual_y < tmp_point.get_y()){
                float adj_hyp = distance(tmp_point,t)/distance(tmp_point,p_mouse);
                adj_hyp = adj_hyp > 1 ? 1 : adj_hyp;
                angle = acosf(adj_hyp);
            }
            else{
                float adj_hyp = distance(tmp_point,t)/distance(tmp_point,p_mouse);
                adj_hyp = adj_hyp > 1 ? 1 : adj_hyp;
                angle = (float)(2*M_PI) - acosf(adj_hyp);
            }
        }
        angle *= -1;
        tmp_item_modified.first->rotate(angle-tmp_angle_rotation);
        tmp_angle_rotation = angle;
        tmp_item_modified.second = tmp_item_modified.first->getItem();
    }

    scene->addItem(tmp_item_modified.second);
}

/**
 * lors du clic de la souris, en fonction du boutton préselectionné la fonction
 * applique différent algorithme :
 * - création de figure vide(ligne, ellipse, polygone)
 * - modification de figure selectionnée(déplacement,agrandissement,rotation,symetrie
 * @param event evenement de la souris
 */
void Window::mousePressEvent(QMouseEvent *event) {
    figure_on_creation = true;
    int actual_x = event->pos().x();
    int actual_y = event->pos().y();
    switch(type_button) {
        case 6:
            //empty line
            tmp_point = Point(actual_x,actual_y);
            queue_point.push_back(tmp_point);
            tmp_line = new QGraphicsLineItem(QLineF(QPointF(actual_x,actual_y),QPointF(actual_x,actual_y)));
            scene->addItem(tmp_line);
            break;
        case 4:
            //empty ellipse
            tmp_point = Point(actual_x,actual_y);
            queue_point.push_back(tmp_point);
            tmp_ellipse = new QGraphicsEllipseItem(actual_x,actual_y,0,0);
            scene->addItem(tmp_ellipse);
            break;
        case 5:
            //empty polygon
            if(list_line_polygon.size() == 0){
                tmp_point = Point(actual_x,actual_y);
                queue_point.push_back(tmp_point);
            }
            tmp_line = new QGraphicsLineItem(QLineF(QPointF(tmp_point.get_x(),tmp_point.get_y()),QPointF(actual_x,actual_y)));
            scene->addItem(tmp_line);
            break;
        case 7:
        {
            //move
            delete_figure_before_modif();
            move_and_add_tmp_item(actual_x,actual_y);
            break;
        }
        case 8:
        {
            //scale
            delete_figure_before_modif();
            scale_and_add_tmp_item(actual_x,actual_y);
            break;
        }
        case 9:
        {
            //rotate
            delete_figure_before_modif();
            rotate_and_add_tmp_item(actual_x,actual_y);
        }

            break;
        case 10:
            //axial sym
            tmp_point = Point(actual_x,actual_y);
            tmp_line = new QGraphicsLineItem(QLineF(QPointF(actual_x,actual_y),QPointF(actual_x,actual_y)));
            scene->addItem(tmp_line);
            break;
        case 11:
            //central sym
            //calculé seulement au release
            break;
        default:
            break;
    }
}


/**
 * pendant le déplacement de la souris, si le clic est enfoncé applique différents algorithmes
 * en fonction du boutton préselectionné :
 * - modification de la figure en cours de création(ligne,ellipse,polygone)
 * - modification de la figure selectionné(déplacement,agrandissement,rotation,symétrie)
 * @param event evenement de la souris
 */
void Window::mouseMoveEvent(QMouseEvent *event) {
    if(figure_on_creation){
        int actual_x = event->pos().x();
        int actual_y = event->pos().y();
        switch(type_button) {
            case 6:
                //line
                scene->removeItem(tmp_line);
                tmp_line = new QGraphicsLineItem(QLineF(QPointF(tmp_point.get_x(),tmp_point.get_y()),QPointF(actual_x,actual_y)));
                scene->addItem(tmp_line);
                break;
            case 4:
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
            case 5:
                //polygon
                scene->removeItem(tmp_line);
                tmp_line = new QGraphicsLineItem(QLineF(QPointF(tmp_point.get_x(),tmp_point.get_y()),QPointF(actual_x,actual_y)));
                scene->addItem(tmp_line);
                break;
            case 7:
            {
                //move
                scene->removeItem(tmp_item_modified.second);
                move_and_add_tmp_item(actual_x,actual_y);
            }

                break;
            case 8:
            {
                //scale
                scene->removeItem(tmp_item_modified.second);
                scale_and_add_tmp_item(actual_x,actual_y);
                break;
            }
            case 9:
            {
                //rotate
                scene->removeItem(tmp_item_modified.second);
                rotate_and_add_tmp_item(actual_x,actual_y);
                break;
            }
            case 10:
                //axial sym
                scene->removeItem(tmp_line);
                tmp_line = new QGraphicsLineItem(QLineF(QPointF(tmp_point.get_x(),tmp_point.get_y()),QPointF(actual_x,actual_y)));
                scene->addItem(tmp_line);
                break;
            case 11:
                //central sym
                //calcul seulement au release
                break;
            default:
                break;
        }
    }
}

/**
 * au relachement du clic de la souris, applique différents algorithmes
 * en fonction du boutton préselectionné :
 * - création final de la figure(ligne,ellipse)
 * - création d'une ligne du polygone
 * - selection de l'item dans la scene
 * - modification final de la figure sélectionnée(déplacement,agrandissement,rotation,symétrie)
 * @param event evenement de la souris
 */
void Window::mouseReleaseEvent(QMouseEvent *event){

    figure_on_creation = false;
    int actual_x = event->pos().x();
    int actual_y = event->pos().y();

    switch(type_button){
        case 6:
        {
            //line
            std::cout << "create line "<< std::endl;
            scene->removeItem(tmp_line);
            queue_point.push_back(Point(actual_x,actual_y));
            tmp_line = nullptr;
            Point A = queue_point[0];
            Point B = queue_point[1];

            QPointF Af = mapToScene(static_cast<int>(A.get_x()),static_cast<int>(A.get_y()));
            QPointF Bf = mapToScene(static_cast<int>(B.get_x()),static_cast<int>(B.get_y()));

            QGraphicsLineItem *l = new QGraphicsLineItem(QLineF(Af,Bf));
            scene->addItem(l);

            std::pair<My_Shape *,QGraphicsItem *> p;
            p.first = new Line(A,B);
            p.second = l;
            list_figure.push_back(p);

            queue_point.clear();
            break;
        }

        case 4:
        {
            //ellipse
            std::cout << "create ellipse " << std::endl;
            queue_point.push_back(Point(actual_x,actual_y));
            scene->removeItem(tmp_ellipse);
            tmp_ellipse = nullptr;
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
            QGraphicsEllipseItem *e = new QGraphicsEllipseItem(O.get_x(),O.get_y(),fabsf(OTX),fabsf(OTY));
            scene->addItem(e);

            std::pair<My_Shape *,QGraphicsItem *> p;
            p.first = new Ellipse(center,fabsf(OTX/2),fabsf(OTY/2));
            p.second = e;
            list_figure.push_back(p);

            queue_point.clear();
            break;
        }

        case 5:
        {
            //polygon
            std::cout << "create line of polygon "<< std::endl;
            scene->removeItem(tmp_line);
            Point A = tmp_point;
            Point B = Point(event->pos().x(),event->pos().y());
            queue_point.push_back(B);

            tmp_line = new QGraphicsLineItem(QLineF(QPointF(A.get_x(),A.get_y()),QPointF(B.get_x(),B.get_y())));
            scene->addItem(tmp_line);
            list_line_polygon.push_back(tmp_line);
            tmp_line = nullptr;

            tmp_point = Point(event->pos().x(),event->pos().y());
            break;
        }

        case 3:
        {
            //selection
            tmp_point = Point(event->pos().x(),event->pos().y());
            tmp_item_modified.second = itemAt(event->pos());
            if(tmp_item_modified.second != nullptr){
                bool itemFind = false;
                //recherche dans la liste la figure correspondante.
                for(std::pair<My_Shape*,QGraphicsItem*> ptmp : list_figure){
                    if(ptmp.second == tmp_item_modified.second){
                        tmp_item_modified.first = ptmp.first;
                        itemFind = true;
                    }
                }
                if(!itemFind){
                    throw "item selectionné introuvable dans les données";
                }
                tmp_point = tmp_item_modified.first->center();
                type_item_modified = tmp_item_modified.second->type();
                enable_buttons();
                if(type_item_modified == 6){
                    m_button_color_background->setDisabled(true);
                }
            }
            else{
                disable_buttons();
                tmp_item_modified.first = nullptr;
            }
            break;
        }

        case 7:
        {
            //move
            scene->removeItem(tmp_item_modified.second);
            move_and_add_tmp_item(actual_x,actual_y);
            list_figure.push_back(tmp_item_modified);
            break;
        }

        case 8:
        {
            //scale
            scene->removeItem(tmp_item_modified.second);
            scale_and_add_tmp_item(actual_x,actual_y);
            list_figure.push_back(tmp_item_modified);
            break;
        }

        case 9:
        {
            //rotate
            scene->removeItem(tmp_item_modified.second);
            rotate_and_add_tmp_item(actual_x,actual_y);
            list_figure.push_back(tmp_item_modified);
            break;
        }

        case 10:
            //axial sym
            delete_figure_before_modif();
            scene->removeItem(tmp_line);
            tmp_item_modified.first->axial_sym(tmp_point,Point(actual_x,actual_y));
            tmp_item_modified.second = tmp_item_modified.first->getItem();
            scene->addItem(tmp_item_modified.second);
            list_figure.push_back(tmp_item_modified);

            break;

        case 11:
            //central sym
            delete_figure_before_modif();
            tmp_item_modified.first->central_sym(Point(actual_x,actual_y));
            tmp_item_modified.second = tmp_item_modified.first->getItem();
            scene->addItem(tmp_item_modified.second);
            list_figure.push_back(tmp_item_modified);
            break;
        default:
            break;
    }
}

