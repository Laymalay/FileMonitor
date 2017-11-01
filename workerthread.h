#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H
#include "mainwindow.h"

class WorkerThread : public QThread
{
     Q_OBJECT
public:
    WorkerThread();
    void run() override;
signals:
    void SliceIsReady(QString fileName, qint64 size, int i, QColor color);
    void finished();
public slots:
    void GetNewTask(QFileInfoList _fileInfoList);
private:
    QFileInfoList _fileInfoList;
};

#endif // WORKERTHREAD_H
