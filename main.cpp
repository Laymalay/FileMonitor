#include "mainwindow.h"
#include "workerthread.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowOpacity(0.95);
    w.setWindowTitle("File System Manager");
    w.showMaximized();

    WorkerThread *workerThread = new WorkerThread();

    QObject::connect(w.pie, SIGNAL(GiveNewTask(QFileInfoList)), workerThread, SLOT(GetNewTask(QFileInfoList)));
    QObject::connect(workerThread, &WorkerThread::SliceIsReady, w.pie, &DirectoryPie::AddSlice);
    QObject::connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
//    workerThread->start();
    return a.exec();
}
