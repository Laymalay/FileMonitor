#ifndef DIRECTORYPIE_H
#define DIRECTORYPIE_H

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QFileSystemModel>
#include <QDebug>
#include <QStack>
#include <QThread>
#include "dirsizecounter.h"

QT_CHARTS_USE_NAMESPACE


class DirectoryPie: public QChartView
{
    Q_OBJECT

public:
     static QColor getRandomColor();
     void updatePie(QFileInfoList fileInfoList, QString directoryName);
     DirectoryPie(QChartView *parent = 0);
     QMap<QString,qint64> *listOfFileSizes;
     QMap<QString,QColor> *listOfColors;
     QPieSeries *series;
    ~DirectoryPie();
private:
    QChart *chart;
    void clearChart();
    QColor getNewTone(int i, QColor color);

public slots:
     void AddSlice(QString fileName, qint64 size, int i, QColor color);
     void onSliceClicked();
     void PieSliceHovered(bool hovered);
signals:
     void AbortWorker();
     void ShowFileInfoSignal(bool hovered, QString fileName);
     void onSliceClickedSignal(QString fileName);
     void GiveNewTask(QFileInfoList _fileInfoList);
};

#endif // DIRECTORYPIE_H
