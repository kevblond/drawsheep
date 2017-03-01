//
// Created by kev on 01/03/17.
//

#ifndef DRAWSHEEP_WINDOW_HPP
#define DRAWSHEEP_WINDOW_HPP

class Window : public QWidget
{
//    Q_OBJECT

public:
    Window();

//public slots:
//    void test_quit();

private:
    QPushButton *m_button_quit;
};

#endif //DRAWSHEEP_WINDOW_HPP
