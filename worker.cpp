#include "worker.h"
#include "directorypie.h"
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
      qint64 size = getFileSize(_fileInfoList.at(i).absoluteFilePath());
      emit SliceIsReady(_fileInfoList.at(i).fileName(),  size, i, color);
    }
    emit finished();
}




qint64 Worker::getFileSize(QString filePath){
    QFileInfo fileInfo(filePath);
    if (fileInfo.isFile()){
        return fileInfo.size();
    }
    else
    {
        return Worker::dirSize(filePath);
    }
}

qint64 Worker::dirSize(QString dirPath)
{
    qint64 totalSize = 0;
    QDir dir(dirPath);
    QFileInfoList fileInfoList = dir.entryInfoList();

    for (int i=0; i < fileInfoList.size(); i++){
            if (fileInfoList.at(i).fileName()!="."&&fileInfoList.at(i).fileName()!=".."){
            if (fileInfoList.at(i).isDir()){
                totalSize+=dirSize(fileInfoList.at(i).absoluteFilePath());
            }
             else {
             totalSize+=fileInfoList.at(i).size();
            }
        }
    }
    return totalSize;
}
QString Worker::sizeHuman(qint64 size)
{
    float num = size;
    QStringList list;
    list << "KB" << "MB" << "GB" << "TB";

    QStringListIterator i(list);
    QString unit("bytes");

    while(num >= 1024.0 && i.hasNext())
     {
        unit = i.next();
        num /= 1024.0;
    }
    return QString().setNum(num,'f',2)+" "+unit;
}


