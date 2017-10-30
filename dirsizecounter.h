#ifndef DIRSIZECOUNTER_H
#define DIRSIZECOUNTER_H
#include <QObject>
#include <QFileSystemModel>


class DirSizeCounter: public QObject {
    Q_OBJECT
public:
    DirSizeCounter(QString filePath);
    static QString sizeHuman(qint64 size);
    static qint64 dirSize(QString dirPath);
    static qint64 getFileSize(QString absPath);
    ~DirSizeCounter();
public slots:
    void process();
signals:
    void SizeCounted(qint64 size);
    void finished();
private:
    QString _filePath;
};

#endif // DIRSIZECOUNTER_H
