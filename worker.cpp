#include "worker.h"
#include "directorypie.h"
#include "dirsizecounter.h"
Worker::Worker()
{

}

Worker::~Worker()
{

}

void Worker::GetNewTask(QFileInfoList fileInfoList)
{
   qDebug()<<"got it!";
   _fileInfoList = fileInfoList;
   process();

}
void Worker::process()
{
    qint64 totalSize = 0;
    QColor color = DirectoryPie::getRandomColor();
    for (int i=0; i < _fileInfoList.size(); i++){
        qint64 size = DirSizeCounter::getFileSize(_fileInfoList.at(i).absoluteFilePath());
        emit SliceIsReady(_fileInfoList.at(i).fileName(), size, i, color);
        totalSize+=size;
        emit SizeProgress(totalSize);
    }
//    emit finished();
}

