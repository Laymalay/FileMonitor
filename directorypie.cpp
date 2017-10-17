#include "directorypie.h"

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
      fileInfoList.at(i).isDir()?
      size = this->dirSize(fileInfoList.at(i).absoluteFilePath()):
      size = fileInfoList.at(i).size();
      //series->append(fileInfoList.at(i).fileName(), size);
      series->append(sizeHuman(size), size);
    }

    for(auto slice : series->slices())
        if (100*slice->percentage()>2.5)
        {
            slice->setLabelPosition(QPieSlice::LabelInsideNormal);
            slice->setLabelVisible();
        }

    this->chart->addSeries(series);
    chart->setTitle(directoryName);
    chart->legend()->hide();

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
                totalSize+=this->dirSize(fileInfoList.at(i).absoluteFilePath());
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


