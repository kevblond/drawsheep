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
        //affichage du point
        //scene->addLine(event->pos().x(),event->pos().y(),event->pos().x(),event->pos().y());
        std::cout << event->pos().x() << " " << event->pos().y() << std::endl;
        switch(type_figure){
            case 0:
                //line
                if(queue_point.size() == 2){
                    std::cout << "create line "<< std::endl;
                    Point A = queue_point[0];
                    Point B = queue_point[1];
                    list_figure.push_back(new Line(A,B));


                    QPointF Af = mapToScene(static_cast<int>(A.get_x()),static_cast<int>(A.get_y()));
                    QPointF Bf = mapToScene(static_cast<int>(B.get_x()),static_cast<int>(B.get_y()));

                    scene->addLine(QLineF(Af,Bf));

                    type_figure = 1;
                    queue_point.clear();
                }
                break;
            case 1:
                //cercle
                if(queue_point.size() == 2){
                    std::cout << "create circle " << std::endl;
                    Point O = queue_point[0];
                    Point T = queue_point[1];
                    float OT = distance(O,T);
                    list_figure.push_back(new Circle(O,OT));

                    QPointF Of = mapToScene(static_cast<int>(O.get_x()),static_cast<int>(O.get_y()));
                    QPointF Tf = mapToScene(static_cast<int>(T.get_x()),static_cast<int>(T.get_y()));
                    float OTf = distance(Point((float)Of.x(),(float)Of.y()),Point((float)Tf.x(),(float)Tf.y()));
                    scene->addEllipse(Of.x(),Of.y(),OTf,OTf);

                    queue_point.clear();
                }
                break;
            case 2:
                //ellipse
                if(queue_point.size() == 3){
                    std::cout << "create ellipse " << std::endl;
                    Point O = queue_point[0];
                    Point A = queue_point[1];
                    Point B = queue_point[2];
                    list_figure.push_back(new Ellipse(O,distance(O,A),distance(O,B)));
                    std::cout << O.get_x() << "," << O.get_y() << std::endl;

                    QPointF Of = mapToScene(static_cast<int>(O.get_x()),static_cast<int>(O.get_y()));
                    QPointF Af = mapToScene(static_cast<int>(A.get_x()),static_cast<int>(A.get_y()));
                    QPointF Bf = mapToScene(static_cast<int>(B.get_x()),static_cast<int>(B.get_y()));
                    int OA = abs(static_cast<int>(Of.x() - Af.x()));
                    int OB = abs(static_cast<int>(Of.y() - Bf.y()));
                    std::cout << Of.x() << "," << Of.y() << " " << OA << " " << OB << std::endl;
                    scene->addEllipse(Of.x(),Of.y(),OA,OB);

                    queue_point.clear();
                }

                break;
            //polygone se fais a part, lorsqu'on clique sur le bouton fermer polygone il se créer.
        }
    }
}

