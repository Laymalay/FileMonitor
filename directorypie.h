#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QFileSystemModel>
#include <QDebug>
#include <QStack>
#ifndef DIRECTORYPIE_H
#define DIRECTORYPIE_H
QT_CHARTS_USE_NAMESPACE


class DirectoryPie: public QChartView
{
    Q_OBJECT

public:
     DirectoryPie(QChartView *parent = 0);
     void updatePie(QFileInfoList fileInfoList, QString directoryName);
     static qint64 dirSize(QString dirPath);
     static QString sizeHuman(qint64 size);
     static qint64 getFileSize(QString absPath);
    ~DirectoryPie();
private:
    QPieSeries *series;
    QChart *chart;
    QMap<QString,QColor> *listOfColors;

private slots:
     void onSliceClicked();
     void PieSliceHovered(bool hovered);
signals:
     void ShowFileInfoSignal(bool hovered, QString fileName);
     void onSliceClickedSignal(QString fileName);
};

#endif // DIRECTORYPIE_H
