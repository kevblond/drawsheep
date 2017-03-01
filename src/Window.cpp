//
// Created by kev on 01/03/17.
//


#include <Window.hpp>

Window::Window() : QWidget() {
    setFixedSize(1500,900);
    m_button_quit = new QPushButton("Quittez",this);
    m_button_quit.setToolTip("ce message s'affiche quand on passe la souris sur le drawing");
    m_button_quit.setFixedSize(100, 100);
    //la souris montre que le bouton est cliquable
    m_button_quit.setCursor(Qt::PointingHandCursor);
    //quand on clique sur le bouton on quitte l'appli
    QObject::connect(&drawing,SIGNAL(clicked()),qApp,SLOT(test_quit()));
}

void Window::test_quit() {

}
