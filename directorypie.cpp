#include "directorypie.h"

DirectoryPie::DirectoryPie(float hole_size, QChartView *parent): QChartView(parent)
{
    this->series = new QPieSeries();
    series->setHoleSize(hole_size);
    series->append("Jane", 20);
    series->append("Joe", 20);
    series->append("Andy", 20);
    series->append("Barbara", 10);
    series->append("Axel", 30);
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
    chart->setTheme(QChart::ChartThemeDark);
    chart->setAnimationOptions(QChart::AllAnimations);

}

DirectoryPie::~DirectoryPie()
{

}

void DirectoryPie::updatePie(float hole_size)
{
    this->series->setHoleSize(hole_size);

}


