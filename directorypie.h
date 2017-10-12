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
     DirectoryPie(float p = 0.2, int p2 = 10 , QChartView *parent = 0);
    ~DirectoryPie();
     float p;
private:




};

#endif // DIRECTORYPIE_H
