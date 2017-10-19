#include "directorypie.h"
#include "mainwindow.h"
DirectoryPie::DirectoryPie(QChartView *parent): QChartView(parent)
{
    this->series = new QPieSeries();
    series->setHoleSize(0.6);
//!!!EXPLODED THE CLICKED SECTOR!!!
//     QPieSlice *slice = series->append("Fat 15.6%", 15.6);
//         slice->setExploded();
//         slice->setLabelVisible();
    this->chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    this->setChart(chart);
    this->setRenderHint(QPainter::Antialiasing);
    chart->setTheme(QChart::ChartThemeDark);
    chart->setBackgroundVisible(false);
    chart->setAnimationOptions(QChart::AllAnimations);

}



void DirectoryPie::updatePie(QFileInfoList fileInfoList, QString directoryName)
{
    this->series = new QPieSeries();
    series->setHoleSize(0.3);


    for (int i=0; i < fileInfoList.size(); i++){
      qint64 size = 0;
      size = getFileSize(fileInfoList.at(i).absoluteFilePath());
      //series->append(fileInfoList.at(i).fileName(), size);
      QPieSlice *slice = new QPieSlice(fileInfoList.at(i).fileName(), size);
      //sizeHuman(size);
      series->append(slice);
      connect(slice,SIGNAL(hovered(bool)),this,SLOT(PieSliceHovered(bool)));
    }

    for(auto slice : series->slices())
        if (100*slice->percentage()>2.5)
        {
            slice->setLabelPosition(QPieSlice::LabelInsideNormal);
            slice->setLabelVisible();
        }
    this->chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    this->setChart(chart);
    this->setRenderHint(QPainter::Antialiasing);
    chart->setTheme(QChart::ChartThemeDark);
    chart->setBackgroundVisible(false);
    chart->setAnimationOptions(QChart::AllAnimations);


//    this->chart->addSeries(series);
    chart->setTitle(directoryName);
//    chart->legend()->hide();

}

qint64 DirectoryPie::getFileSize(QString filePath){
    QFileInfo fileInfo(filePath);
    if (fileInfo.isFile()){
        return fileInfo.size();
    }
    else
    {
        return DirectoryPie::dirSize(filePath);
    }
}

qint64 DirectoryPie::dirSize(QString dirPath)
{
    qint64 totalSize = 0;
    QDir dir(dirPath);
    QFileInfoList fileInfoList = dir.entryInfoList();

    for (int i=0; i < fileInfoList.size(); i++){
            qDebug()<< fileInfoList.at(i).fileName();
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
QString DirectoryPie::sizeHuman(qint64 size)
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

DirectoryPie::~DirectoryPie()
{
}

void DirectoryPie::PieSliceHovered(bool hovered)
{
    QPieSlice* ptr = ((QPieSlice*)sender());
    ptr->setExploded(hovered);
    emit ShowFileInfoSignal(hovered, ptr->label());
}


