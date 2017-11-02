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

    QThread* thread = new QThread;
    Worker* worker = new Worker();
    qRegisterMetaType<QFileInfoList>("QFileInfoList");
    QObject::connect(w.pie, SIGNAL(GiveNewTask(QFileInfoList)), worker, SLOT(GetNewTask(QFileInfoList)));
    QObject::connect(worker,SIGNAL(SliceIsReady(QString, qint64, int, QColor)),w.pie,SLOT(AddSlice(QString, qint64, int, QColor)));
    QObject::connect(worker, &Worker::SizeProgress, &w, &MainWindow::ShowDirSizelabel);
    QObject::connect(worker, SIGNAL (finished()), thread, SLOT (quit()));
    QObject::connect(worker, SIGNAL (finished()), worker, SLOT (deleteLater()));
    QObject::connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    worker->moveToThread(thread);
    thread->moveToThread(thread);
    thread->start();



//    WorkerThread *workerThread = new WorkerThread();
//    QObject::connect(w.pie, SIGNAL(GiveNewTask(QFileInfoList)), workerThread, SLOT(GetNewTask(QFileInfoList)));
//    QObject::connect(workerThread, &WorkerThread::SliceIsReady, w.pie, &DirectoryPie::AddSlice);
//    QObject::connect(workerThread, &WorkerThread::SizeProgress, &w, &MainWindow::ShowDirSizelabel);
//    QObject::connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
//    workerThread->start(QThread::IdlePriority);
    return a.exec();
}
