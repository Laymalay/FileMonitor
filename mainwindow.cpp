#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QFileSystemModel>
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
    //    ui->DirTreeView->clear();
    //ui->DirTreeView->setSortingEnabled(true);
    watcher = new QFileSystemWatcher(this);
    watcher->addPath(path);

    disconnect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(NotifyChanges(QString)));
    QDir dir(path);
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileSystemModel* modelTree = new QFileSystemModel(this);
    modelTree->setRootPath(path);
    QModelIndex idx = modelTree->index(path);
    ui->DirTreeView->setModel(modelTree);
    ui->DirTreeView->setRootIndex(idx);

//    QFileInfoList list =dir.entryInfoList();
//    ui->DirTreeView->addItems(list);
//    for(int i=0; i<list.size();++i){
//        ui->DirTreeView->addItem(list.at(i).fileName());
//    }
     connect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(NotifyChanges(QString)));
     connect(watcher, SIGNAL(fileChanged(QString)), this, SLOT(NotifyChanges(QString)));
}

void MainWindow::NotifyChanges(const QString &path)
{
    qDebug() << "Signal Reseved!";
//    QStringList oldList, newList;
//    for(int i=0; i<ui->DirTreeView->count();i++){
//        QListWidgetItem *item =  ui->DirTreeView->item(i);
//        if (item->text()!='.'&&item->text()!=".."){
//            oldList << item->text();
//        }
//    }
//    qSort(oldList);


//    QDir dir(path);
//    QFileInfoList list =dir.entryInfoList();
//    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
//    dir.setSorting(QDir::Size | QDir::Reversed);
//    for(int i=0; i<list.size();++i){
//         if (list.at(i).fileName()!='.'&&list.at(i).fileName()!=".."){
//            newList << list.at(i).fileName();
//         }
//    }
//    qSort(newList);


//    QSet<QString> intersection;
//    if(oldList.count()>newList.count()){
//        ui->DirTreeView->clear();
//        intersection = oldList.toSet().intersect(newList.toSet());
//        foreach (const QString &value, intersection) {
//            ui->DirTreeView->addItem(value);
//        }
//        ui->lblStatus->setText("[!]File removed");
//    }
//    else if(oldList.count()<newList.count()){
//        intersection = newList.toSet().subtract(oldList.toSet());
//        foreach (const QString &value, intersection) {
//            QListWidgetItem *wi = new QListWidgetItem();
//            wi->setText(value);
//            wi->setForeground(Qt::green);
//            ui->DirTreeView->addItem(wi);
//        }
//         ui->lblStatus->setText("[!]File added");

//    }else{
//         ui->lblStatus->setText("[!]File modified");
//    }
    //TODO: add update function after file modifieded
    //add file sizes
    //add settings
    //add save program state
}
