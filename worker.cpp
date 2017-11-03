#include "worker.h"
#include "directorypie.h"
#include "dirsizecounter.h"
Worker::Worker()
{
    abort = false;
}

Worker::~Worker()
{

}

void Worker::GetNewTask(QFileInfoList fileInfoList)
{
   qDebug()<<"got it!";
   abort = false;
   _fileInfoList = fileInfoList;
   process();

}

void Worker::process()
{
    qint64 totalSize = 0;
    QColor color = DirectoryPie::getRandomColor();
    for (int i=0; i < _fileInfoList.size(); i++){
        if (_fileInfoList.size()>100)
            QThread::msleep(100);
        if (abort){
            break;
        }
        qint64 size = DirSizeCounter::getFileSize(_fileInfoList.at(i).absoluteFilePath());
        emit SliceIsReady(_fileInfoList.at(i).fileName(), size, i, color);
        totalSize+=size;
        emit SizeProgress(totalSize);
    }
    emit finish();
    //    emit finished();
}

void Worker::Abort()
{
    abort = true;
}

