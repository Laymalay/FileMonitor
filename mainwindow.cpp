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
    pie->setStyleSheet("background:transparent;");
    ui->charts->addWidget(pie);
    QColor *color = new QColor();
    color->setRgb((rand() % 255),(rand() % 255),(rand() % 255));
    this->setCentralWidget(ui->splitter);
    ui->DirTreeView->setStyleSheet(
                "QHeaderView::section{ background-color: rgba(137, 137, 137, 33);\
                                        color:white}"
                "QTreeView{color:white}");
    connect(pie,SIGNAL(onSliceClickedSignal(QString)),this,SLOT(onSliceClicked(QString)));
    connect(pie,SIGNAL(ShowFileInfoSignal(bool, QString)),this,SLOT(ShowFileInfo(bool, QString)));
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
    qDebug()<< fileName;
    path = path + "/" + fileName;
    QFileInfo fileInfo(path);
    if (fileInfo.isDir())
        updateWindow(path);
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
}

void MainWindow::ShowFileInfo(bool hovered, QString fileName)
{
    QString absPath = path + "/" +fileName;
    QFileInfo fileInfo(absPath);
    ui->fileInfo->setText(fileName +"\n" + DirectoryPie::sizeHuman(DirectoryPie::getFileSize(absPath)));

}
