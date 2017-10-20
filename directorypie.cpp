#include "directorypie.h"

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
    listOfColors = new QMap<QString,QColor>;
    QColor *color = new QColor();
    int x = rand() % 255;
    int y = rand() % 255;
    int z = rand() % 255;
    int xx=0,yy=0,zz=0;
    for (int i=0; i < fileInfoList.size(); i++){
      qint64 size = 0;
      size = getFileSize(fileInfoList.at(i).absoluteFilePath());
      QPieSlice *slice = new QPieSlice(fileInfoList.at(i).fileName(), size);
      xx=(x+(i*30)%150);
      yy=(y+(i*30)%150);
      zz=(z+(i*30)%150);
      if(xx>255)xx=x;
      if(yy>255)yy=y;
      if(zz>255)zz=z;

      color->setRgb(xx,yy,zz);
      slice->setColor(*color);
      listOfColors->insert(fileInfoList.at(i).fileName(),*color);
      slice->setLabelColor(Qt::white);
      connect(slice,SIGNAL(hovered(bool)),this, SLOT(PieSliceHovered(bool)));
      connect(slice,SIGNAL(clicked()),this, SLOT(onSliceClicked()));
      series->append(slice);
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
//    chart->setTheme(QChart::ChartThemeBlueCerulean);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTitle(directoryName);

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

void DirectoryPie::onSliceClicked()
{
    QPieSlice* slice = ((QPieSlice*)sender());
    emit onSliceClickedSignal(slice->label());
}


void DirectoryPie::PieSliceHovered(bool hovered)
{
    QPieSlice* slice = ((QPieSlice*)sender());
    slice->setExploded(hovered);
    QColor hoveredColor,oldColor;
    oldColor = listOfColors->value(slice->label());
    hoveredColor = Qt::white;
    hovered?slice->setColor(hoveredColor):slice->setColor(oldColor);
    hovered?slice->setLabelColor(Qt::black):slice->setLabelColor(Qt::white);
    emit ShowFileInfoSignal(hovered, slice->label());
}


