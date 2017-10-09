#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
QT_CHARTS_USE_NAMESPACE
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPieSeries *series = new QPieSeries();
    series->append("Jane", 1);
    series->append("Joe", 2);
    series->append("Andy", 3);
    series->append("Barbara", 4);
    series->append("Axel", 5);

//    QPieSlice *slice = series->slices().at(1);
//    slice->setExploded();
//    slice->setLabelVisible();
//    slice->setPen(QPen(Qt::darkGreen, 2));
//    slice->setBrush(Qt::green);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Simple piechart example");
    chart->legend()->hide();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->chartsLayout->addWidget(chartView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnBrowse_clicked()
{
    path = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                             ".", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->txtPath->setText(path);
    ui->folderList->clear();

    watcher = new QFileSystemWatcher(this);
    watcher->addPath(path);

    disconnect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(NotifyChanges(QString)));
    QDir dir(path);
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list =dir.entryInfoList();
    for(int i=0; i<list.size();++i){
        ui->folderList->addItem(list.at(i).fileName());
    }
     connect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(NotifyChanges(QString)));
     connect(watcher, SIGNAL(fileChanged(QString)), this, SLOT(NotifyChanges(QString)));
}

void MainWindow::NotifyChanges(const QString &path)
{
    qDebug() << "Signal Reseved!";
    QStringList oldList, newList;
    for(int i=0; i<ui->folderList->count();i++){
        QListWidgetItem *item =  ui->folderList->item(i);
        if (item->text()!='.'&&item->text()!=".."){
            oldList << item->text();
        }


    }
    qSort(oldList);


    QDir dir(path);
    QFileInfoList list =dir.entryInfoList();
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    dir.setSorting(QDir::Size | QDir::Reversed);
    for(int i=0; i<list.size();++i){
         if (list.at(i).fileName()!='.'&&list.at(i).fileName()!=".."){
            newList << list.at(i).fileName();
         }
    }
    qSort(newList);


    QSet<QString> intersection;
    if(oldList.count()>newList.count()){
        ui->folderList->clear();
        intersection = oldList.toSet().intersect(newList.toSet());
        foreach (const QString &value, intersection) {
            ui->folderList->addItem(value);
        }
        ui->lblStatus->setText("[!]File removed");
    }
    else if(oldList.count()<newList.count()){
        intersection = newList.toSet().subtract(oldList.toSet());
        foreach (const QString &value, intersection) {
            QListWidgetItem *wi = new QListWidgetItem();
            wi->setText(value);
            wi->setForeground(Qt::green);
            ui->folderList->addItem(wi);
        }
         ui->lblStatus->setText("[!]File added");

    }else{
         ui->lblStatus->setText("[!]File modified");
    }
    //TODO: add update function after file modifieded
    //add file sizes
    //add settings
    //add save program state





}
