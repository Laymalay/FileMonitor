#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QFileSystemModel>
#include <QDebug>
#ifndef DIRECTORYPIE_H
#define DIRECTORYPIE_H
QT_CHARTS_USE_NAMESPACE


class DirectoryPie: public QChartView
{
    Q_OBJECT

public:
     DirectoryPie(QChartView *parent = 0);
     void updatePie(QFileInfoList fileInfoList, QString directoryName);
     qint64 dirSize(QString dirPath);
    ~DirectoryPie();
private:
    QPieSeries *series;
    QChart *chart;

};

#endif // DIRECTORYPIE_H
