#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowOpacity(0.95);
    w.setWindowTitle("File System Manager");
    w.showMaximized();
    connect(w.pie,w.pie::UpdatePieWorker,UpdatePieSlot);
    connect(w,&Sender::CountDirSize(DirSizeCounter*),CountDirSize(DirSizeCounter*));


    return a.exec();
}
void UpdatePieSlot(Worker* worker){
    QThread* thread = new QThread;
    worker->moveToThread(thread);
    connect(worker,SIGNAL(SliceIsReady(QString, qint64, int, QColor)),w.pie,SLOT(AddSlice(QString, qint64, int, QColor)));
    connect(thread, SIGNAL (started()), worker, SLOT (process()));
    connect(worker, SIGNAL (finished()), thread, SLOT (quit()));
    connect(worker, SIGNAL (finished()), worker, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();
}

void CountDirSize(DirSizeCounter* worker){
    QThread* thread = new QThread;
    worker->moveToThread(thread);
    connect(worker,SIGNAL(SizeCounted(qint64)),w,SLOT(ShowDirSizelabel(qint64)));
    connect(thread, SIGNAL (started()), worker, SLOT (process()));
    connect(worker, SIGNAL (finished()), thread, SLOT (quit()));
    connect(worker, SIGNAL (finished()), worker, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();
}
