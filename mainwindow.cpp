#include "mainwindow.h"
#include "directorypie.h"
#include "ui_mainwindow.h"
#include <QFileSystemModel>
#include "worker.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    dirSizelbl = new QLabel();
    dirSizelbl->setAlignment(Qt::AlignCenter);
    ui->charts->addWidget(dirSizelbl);
    dirSizelbl->setStyleSheet("background:transparent; color: white; font: 20px");
    dirSizelbl->setMinimumWidth(500);

    QHBoxLayout* topLayout = new QHBoxLayout(dirSizelbl);
    ui->charts->addLayout(topLayout);

    pie = new DirectoryPie();
    pie->setStyleSheet("background:transparent;");
    topLayout->addWidget(pie);

    fileInfolbl = new QLabel();
    fileInfolbl->setVisible(false);
    fileInfolbl->setAlignment(Qt::AlignCenter);
    fileInfolbl->setStyleSheet("background:transparent; color: white; font: 20px");
    ui->charts->addWidget(fileInfolbl);


    QColor *color = new QColor();
    color->setRgb((rand() % 255),(rand() % 255),(rand() % 255));
    this->setCentralWidget(ui->splitter);

    ui->DirTreeView->setStyleSheet(
                "QHeaderView::section{ background-color: rgba(137, 137, 137, 33);\
                                        color:white}"
                "QTreeView{color:white}");
    connect(pie,SIGNAL(onSliceClickedSignal(QString)),this,SLOT(onSliceClicked(QString)));
    connect(pie,SIGNAL(ShowFileInfoSignal(bool, QString)),this,SLOT(ShowFileInfo(bool, QString)));
    pathStack = new QStack<QString>;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnBrowse_clicked()
{
    path = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                             ".", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    updateWindow(path);
}


void MainWindow::onSliceClicked(QString fileName)
{
    QString newPath = path + "/" + fileName;
    QFileInfo fileInfo(newPath);
    if (fileInfo.isDir()){
        pathStack->push(path);
        path = newPath;
        updateWindow(path);
    }
}

void MainWindow::updateWindow(QString path)
{
    ui->txtPath->setText(path);
    QDir dir(path);
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileSystemModel* modelTree = new QFileSystemModel(this);
    modelTree->setRootPath(path);
    QModelIndex idx = modelTree->index(path);

    ui->DirTreeView->setModel(modelTree);
    ui->DirTreeView->setRootIndex(idx);

    QFileInfoList fileInfoList= dir.entryInfoList();
    pie->updatePie(fileInfoList, dir.dirName());
    dirSizelbl->setText(Worker::sizeHuman(Worker::dirSize(path)));
}

void MainWindow::ShowFileInfo(bool hovered, QString fileName)
{
    QString absPath = path + "/" +fileName;
    QFileInfo fileInfo(absPath);
    fileInfolbl->setText(fileName +"\n" + Worker::sizeHuman(pie->listOfFileSizes->value(fileName)));
    hovered?fileInfolbl->setVisible(true):fileInfolbl->setVisible(false);
}




void MainWindow::on_btnback_clicked()
{
    if (!pathStack->isEmpty()){
        path = pathStack->pop();
        updateWindow(path);
    }

}
