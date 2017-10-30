#ifndef WORKER_H
#define WORKER_H
#include <QObject>
#include <QFileSystemModel>
#include "directorypie.h"

class Worker : public QObject {
    Q_OBJECT
public:
    Worker(QFileInfoList fileInfoList);
    ~Worker();
public slots:
    void process();
signals:
    void SliceIsReady(QString fileName, qint64 size, int i, QColor color);
    void finished();
private:
    QFileInfoList _fileInfoList;
};

#endif // WORKER_H


