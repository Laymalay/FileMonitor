#ifndef WORKER_H
#define WORKER_H
#include <QObject>
#include <QFileSystemModel>
#include "directorypie.h"

class Worker : public QObject {
    Q_OBJECT
public:
    Worker(QFileInfoList fileInfoList, DirectoryPie *pie);
    static QString sizeHuman(qint64 size);
    ~Worker();
public slots:
    void process();
signals:
    void SliceIsReady(QString fileName, qint64 size, int i, QColor color);
    void finished();
private:
    QFileInfoList _fileInfoList;
    DirectoryPie *_pie;
    qint64 dirSize(QString dirPath);
    qint64 getFileSize(QString absPath);
};

#endif // WORKER_H


