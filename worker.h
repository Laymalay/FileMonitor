#ifndef WORKER_H
#define WORKER_H
#include <QObject>
#include <QFileSystemModel>
#include "directorypie.h"

class Worker : public QObject {
    Q_OBJECT
public:
    Worker(QFileInfoList fileInfoList);
    static QString sizeHuman(qint64 size);
    static qint64 dirSize(QString dirPath);
    ~Worker();
public slots:
    void process();
signals:
    void SliceIsReady(QString fileName, qint64 size, int i, QColor color);
    void finished();
private:
    QFileInfoList _fileInfoList;
    qint64 getFileSize(QString absPath);
};

#endif // WORKER_H


