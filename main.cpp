#include "mainwindow.h"
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
    QObject::connect(w.pie,&DirectoryPie::AbortWorker, worker, &Worker::Abort);
    QObject::connect(&w,&MainWindow::AbortWorker, worker, &Worker::Abort);
    QObject::connect(w.pie,&DirectoryPie::GiveNewTask, worker, &Worker::GetNewTask);
    QObject::connect(worker,&Worker::SliceIsReady,w.pie,&DirectoryPie::AddSlice);
    QObject::connect(worker,&Worker::finish,&w,&MainWindow::StopLoadingAnimation);
    QObject::connect(worker, &Worker::SizeProgress, &w, &MainWindow::ShowDirSizelabel);
    QObject::connect(worker, &Worker::finished, thread, &QThread::quit);
    QObject::connect(worker, &Worker::finished, worker, &Worker::deleteLater);
    QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater);
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
