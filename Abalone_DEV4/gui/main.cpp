#include "maincontroller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainController mainController;
    mainController.start();

    return a.exec();
}
