#include "directorypie.h"

DirectoryPie::DirectoryPie(float p1, int p2, QChartView *parent): QChartView(parent)
{
    p = p1;
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(p);
    series->append("Jane", 1);
    series->append("Joe", 2);
    series->append("Andy", 3);
    series->append("Barbara", 4);
    series->append("Axel", 5);
//!!!EXPLODED THE CLICKED SECTOR!!!
//     QPieSlice *slice = series->append("Fat 15.6%", 15.6);
//         slice->setExploded();
//         slice->setLabelVisible();
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Simple piechart example");
    chart->legend()->hide();
    this->setChart(chart);
    //QChartView *chartView = new QChartView(chart);
    //chartView->setRenderHint(QPainter::Antialiasing);
    //chartView->chart()->setTheme(QChart::ChartThemeDark);
    this->setRenderHint(QPainter::Antialiasing);
    this->chart()->setTheme(QChart::ChartThemeDark);

}

DirectoryPie::~DirectoryPie()
{

}


