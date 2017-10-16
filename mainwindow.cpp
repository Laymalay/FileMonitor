#include "mainwindow.h"
#include "directorypie.h"
#include "ui_mainwindow.h"
#include <QFileSystemModel>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pie = new DirectoryPie();
    pie->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->horizontalLayout_3->addWidget(pie);


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

    watcher = new QFileSystemWatcher(this);
    watcher->addPath(path);

    disconnect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(NotifyChanges(QString)));
    QDir dir(path);
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileSystemModel* modelTree = new QFileSystemModel(this);
    modelTree->setRootPath(path);
    QModelIndex idx = modelTree->index(path);

//==============================================================
//    QList<QString> filesInfoList;
//    int rowCount = modelTree->rowCount(idx);

//    do{qDebug()<<rowCount<<"SDFaasewg";}while(rowCount==0);



//    for (int row = 0; row < rowCount; ++row) {
//        QModelIndex childIndex = modelTree->index(row, 0, idx);
//        QString size = modelTree->fileName(childIndex);
//        filesInfoList.append(size);
//        qDebug()<<size;
//    }
//==============================================================






    ui->DirTreeView->setModel(modelTree);
    ui->DirTreeView->setRootIndex(idx);

    connect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(NotifyChanges(QString)));
    connect(watcher, SIGNAL(fileChanged(QString)), this, SLOT(NotifyChanges(QString)));
    QFileInfoList fileInfoList= dir.entryInfoList();
    for (int i = 0; i < fileInfoList.size(); i++)
    {
        qDebug() << "Filename " + QString::number(i) + " = " + fileInfoList.at(i).filePath()
                    + QString::number(fileInfoList.at(i).size()) + "sgfws"+fileInfoList.at(i).isDir();
    }

    pie->updatePie(fileInfoList, dir.dirName());
}

















//void MainWindow::NotifyChanges(const QString &path)
//{
//    qDebug() << "Signal Reseved!";
////    QStringList oldList, newList;
////    for(int i=0; i<ui->DirTreeView->count();i++){
////        QListWidgetItem *item =  ui->DirTreeView->item(i);
////        if (item->text()!='.'&&item->text()!=".."){
////            oldList << item->text();
////        }
////    }
////    qSort(oldList);


////    QDir dir(path);
////    QFileInfoList list =dir.entryInfoList();
////    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
////    dir.setSorting(QDir::Size | QDir::Reversed);
////    for(int i=0; i<list.size();++i){
////         if (list.at(i).fileName()!='.'&&list.at(i).fileName()!=".."){
////            newList << list.at(i).fileName();
////         }
////    }
////    qSort(newList);


////    QSet<QString> intersection;
////    if(oldList.count()>newList.count()){
////        ui->DirTreeView->clear();
////        intersection = oldList.toSet().intersect(newList.toSet());
////        foreach (const QString &value, intersection) {
////            ui->DirTreeView->addItem(value);
////        }
////        ui->lblStatus->setText("[!]File removed");
////    }
////    else if(oldList.count()<newList.count()){
////        intersection = newList.toSet().subtract(oldList.toSet());
////        foreach (const QString &value, intersection) {
////            QListWidgetItem *wi = new QListWidgetItem();
////            wi->setText(value);
////            wi->setForeground(Qt::green);
////            ui->DirTreeView->addItem(wi);
////        }
////         ui->lblStatus->setText("[!]File added");

////    }else{
////         ui->lblStatus->setText("[!]File modified");
////    }
//    //TODO: add update function after file modifieded
//    //add file sizes
//    //add settings
//    //add save program state
//}
