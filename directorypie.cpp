#include "directorypie.h"

DirectoryPie::DirectoryPie(float hole_size, QChartView *parent): QChartView(parent)
{
    this->series = new QPieSeries();
    series->setHoleSize(hole_size);
    series->append("Jane", 1);
    series->append("Joe", 2);
    series->append("Andy", 3);
    series->append("Barbara", 4);
    series->append("Axel", 5);
//!!!EXPLODED THE CLICKED SECTOR!!!
//     QPieSlice *slice = series->append("Fat 15.6%", 15.6);
//         slice->setExploded();
//         slice->setLabelVisible();
    this->chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Simple piechart example");
    chart->legend()->hide();
    this->setChart(chart);
    //QChartView *chartView = new QChartView(chart);
    //chartView->setRenderHint(QPainter::Antialiasing);
    //chartView->chart()->setTheme(QChart::ChartThemeDark);
    this->setRenderHint(QPainter::Antialiasing);
    this->chart->setTheme(QChart::ChartThemeDark);

}

DirectoryPie::~DirectoryPie()
{

}

void DirectoryPie::updatePie(float hole_size)
{
    this->series->setHoleSize(hole_size);

}


