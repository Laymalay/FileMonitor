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
      qDebug ()<< "pie"+QString::number(size);
      series->append(fileInfoList.at(i).fileName(), size);
    }
    this->chart->addSeries(series);
    chart->setTitle(directoryName);
}

qint64 DirectoryPie::dirSize(QString dirPath)
{
    qint64 totalSize = 0;
    QDir dir(dirPath);
    QFileInfoList fileInfoList = dir.entryInfoList();

    for (int i=0; i < fileInfoList.size(); i++){
        if (fileInfoList.at(i).baseName() != ""){
            qDebug()<< fileInfoList.at(i).baseName();
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

DirectoryPie::~DirectoryPie()
{
}


