#include "directorypie.h"
#include "mainwindow.h"
DirectoryPie::DirectoryPie(QChartView *parent): QChartView(parent)
{
    this->series = new QPieSeries();
    series->setHoleSize(0.6);
    this->chart = new QChart();
    this->setChart(chart);
    chart->setBackgroundVisible(false);
}



void DirectoryPie::updatePie(QFileInfoList fileInfoList, QString directoryName)
{
    this->series = new QPieSeries();
    series->setHoleSize(0.3);
    QColor *color = new QColor();
    listOfColors = new QMap<QString,QColor>;
    int x = rand() % 255;
    int y = rand() % 255;
    int z = rand() % 255;
    int xx=0,yy=0,zz=0;
    for (int i=0; i < fileInfoList.size(); i++){
      qint64 size = 0;
      size = getFileSize(fileInfoList.at(i).absoluteFilePath());
      QPieSlice *slice = new QPieSlice(fileInfoList.at(i).fileName(), size);

      if(x<255) xx=x+(i*10)%255;
      if(y<255) yy=y+(i*40)%255;
      if(z<255) zz=z+(i*60)%255;
      if(xx>255) xx=255;
      if(yy>255) yy=255;
      if(zz>255) zz=255;

      series->append(slice);
      color->setRgb(xx,yy,zz);
      slice->setColor(*color);
      slice->setLabelColor(Qt::white);
      listOfColors->insert(fileInfoList.at(i).fileName(),*color);
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
    QPieSlice* slice = ((QPieSlice*)sender());
    slice->setExploded(hovered);
    QColor hoveredColor,oldColor;
    qDebug()<<hovered;
    qDebug()<<slice->label();
    oldColor = listOfColors->value(slice->label());
    qDebug()<<hovered;
    qDebug()<<oldColor;
    qDebug()<<slice->label();
    qDebug()<<"-----------------------------";
    hoveredColor = Qt::white;
    hovered?slice->setColor(hoveredColor):slice->setColor(oldColor);
    hovered?slice->setLabelColor(Qt::black):slice->setLabelColor(Qt::white);
    emit ShowFileInfoSignal(hovered, slice->label());
}


