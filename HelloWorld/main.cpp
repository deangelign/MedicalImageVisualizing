#include "mainwindow.h"
#include <QApplication>


int windowWidth = 1024;
int windowHeight = 1024;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setGeometry(0,0,windowWidth,windowHeight);
    w.showMaximized();

    return a.exec();
}
