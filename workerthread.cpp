#include "workerthread.h"


WorkerThread::WorkerThread()
{
}

void WorkerThread::GetNewTask(QFileInfoList fileInfoList)
{
   qDebug()<<"got it!";
   _fileInfoList = fileInfoList;
    run();

}
void WorkerThread::run(){
    qint64 totalSize = 0;
    QColor color = DirectoryPie::getRandomColor();
    for (int i=0; i < _fileInfoList.size(); i++){
        qint64 size = DirSizeCounter::getFileSize(_fileInfoList.at(i).absoluteFilePath());
        emit SliceIsReady(_fileInfoList.at(i).fileName(),  size, i, color);
        totalSize+=size;
        emit SizeProgress(totalSize);
        }
    emit finished();
    exec();
    }


