#include "worker.h"
#include "directorypie.h"
#include "dirsizecounter.h"
Worker::Worker(QFileInfoList fileInfoList)
{
    _fileInfoList = fileInfoList;
}

Worker::~Worker()
{

}

void Worker::process()
{
    QColor color = DirectoryPie::getRandomColor();
    for (int i=0; i < _fileInfoList.size(); i++){
      qint64 size = DirSizeCounter::getFileSize(_fileInfoList.at(i).absoluteFilePath());
      emit SliceIsReady(_fileInfoList.at(i).fileName(),  size, i, color);
    }
    emit finished();
}



