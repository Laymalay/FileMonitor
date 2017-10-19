#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowOpacity(0.95);
    w.setWindowTitle("File System Manager");
    //w.show();
    w.showMaximized();
    //w.showFullScreen();
    return a.exec();
}
