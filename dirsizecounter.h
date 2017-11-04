#ifndef DIRSIZECOUNTER_H
#define DIRSIZECOUNTER_H
#include <QObject>
#include <QFileSystemModel>


class DirSizeCounter: public QObject {
    Q_OBJECT
public:
    DirSizeCounter();
    static QString sizeHuman(qint64 size);
    static qint64 dirSize(QString dirPath);
    static qint64 getFileSize(QString absPath);
    ~DirSizeCounter();

};

#endif // DIRSIZECOUNTER_H
