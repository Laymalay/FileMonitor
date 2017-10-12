#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#ifndef DIRECTORYPIE_H
#define DIRECTORYPIE_H
QT_CHARTS_USE_NAMESPACE


class DirectoryPie: public QChartView
{
    Q_OBJECT

public:
     DirectoryPie(float hole_size = 0.5, QChartView *parent = 0);
     void updatePie(float hole_size);
    ~DirectoryPie();
private:
    QPieSeries *series;
    QChart *chart;


};

#endif // DIRECTORYPIE_H
