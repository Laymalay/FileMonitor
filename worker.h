#ifndef WORKER_H
#define WORKER_H
#include <QObject>
#include<QFileSystemModel>
#include "directorypie.h"

class Worker: public QObject
{
    Q_OBJECT
public:
    Worker();
    ~Worker();
public slots:
    void process();
    void Abort();
    void GetNewTask(QFileInfoList _fileInfoList);
signals:
    void SliceIsReady(QString fileName, qint64 size, int i, QColor color);
    void finished();
    void finish();
    void SizeProgress(qint64 size);
private:
    QFileInfoList _fileInfoList;
    bool abort;
};


#endif // WORKER_H
