#include <iostream>
#include <My_Shape.hpp>
#include <Ellipse.hpp>
#include <Polygon.hpp>
#include <Line.hpp>
#include <Window.hpp>
#include <QApplication>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    Window *window = new Window();
    window->show();
    return app.exec();
}