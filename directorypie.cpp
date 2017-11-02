#include "directorypie.h"


DirectoryPie::DirectoryPie(QChartView *parent): QChartView(parent)
{
    this->series = new QPieSeries();
    series->setHoleSize(0.3);
    this->chart = new QChart();
    chart->addSeries(series);
    this->setChart(chart);
    this->listOfColors = new QMap<QString,QColor>;
    this->listOfFileSizes = new QMap<QString,qint64>;
    chart->setBackgroundVisible(false);
    chart->legend()->hide();
    this->setRenderHint(QPainter::Antialiasing);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setAnimationDuration(1000);
}

void DirectoryPie::updatePie(QFileInfoList fileInfoList, QString directoryName)
{
    clearChart();
    chart->setTitle(directoryName);
    emit GiveNewTask(fileInfoList);
    qDebug()<<"give it!";

//    for(auto slice : series->slices())
//        if (100*slice->percentage()>2.5)
//        {
//            slice->setLabelPosition(QPieSlice::LabelInsideNormal);
//            slice->setLabelVisible();
//        }
}

DirectoryPie::~DirectoryPie()
{
    chart->deleteLater();
    series->deleteLater();
    listOfColors->~QMap();
    listOfFileSizes->~QMap();
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


void DirectoryPie::clearChart()
{
      series->clear();
      listOfColors->clear();
      listOfFileSizes->clear();
}

void DirectoryPie::AddSlice(QString fileName, qint64 size, int i,QColor color)
{
    listOfFileSizes->insert(fileName, size);
    QPieSlice *slice = new QPieSlice(fileName, size);
    QColor newTone = getNewTone(i, color);
    slice->setColor(newTone);
    listOfColors->insert(fileName, newTone);
    slice->setLabelColor(Qt::white);
    series->append(slice);
    slice->setLabelPosition(QPieSlice::LabelInsideNormal);
    slice->setLabelVisible();
    connect(slice,SIGNAL(hovered(bool)),this, SLOT(PieSliceHovered(bool)));
    connect(slice,SIGNAL(clicked()),this, SLOT(onSliceClicked()));

}

QColor DirectoryPie::getRandomColor(){
    QColor color;
    int x = rand() % 255;
    int y = rand() % 255;
    int z = rand() % 255;

    color.setRgb(x,y,z);
    return color;
}

QColor DirectoryPie::getNewTone(int i, QColor color){
    int xx = 0, yy = 0, zz = 0;
    int x = color.red();
    int y = color.green();
    int z = color.blue();
    if (x + y + z >700)
    {
        x-=100;
        y-=100;
        z-=100;
    }
    xx=(x+(i*30)%150);
    yy=(y+(i*30)%150);
    zz=(z+(i*30)%150);

    if(xx>255)xx=x;
    if(yy>255)yy=y;
    if(zz>255)zz=z;
    QColor newTone;
    newTone.setRgb(xx,yy,zz);
    return newTone;
}
