#include "mainwindow.h"
#include "directorypie.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    movie = new QMovie(":/gif/load2.gif");
    pie = new DirectoryPie();
    pie->setStyleSheet("background:transparent;");
    ui->charts->addWidget(pie);


    dirSizelbl = new QLabel();
    dirSizelbl->setAlignment(Qt::AlignCenter);
    dirSizelbl->setStyleSheet("background:transparent; color: white; font: 20px");
    dirSizelbl->setMaximumSize(100,100);




    QHBoxLayout* topLayout = new QHBoxLayout(pie);
    topLayout->addWidget(dirSizelbl);


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

    fileInfolbl = new QLabel();
    fileInfolbl->setVisible(false);
    fileInfolbl->setAlignment(Qt::AlignCenter);
    fileInfolbl->setStyleSheet("background:transparent; color: white; font: 10px");
    fileInfolbl->setParent(pie);

    loadinglbl = new QLabel();
    loadinglbl->setAlignment(Qt::AlignCenter);
    loadinglbl->setStyleSheet("background:transparent; color: white; font: 20px");
    loadinglbl->setMaximumSize(50,50);
    loadinglbl->setParent(dirSizelbl);
    loadinglbl->show();
    loadinglbl->setGeometry(dirSizelbl->width()/2-30,dirSizelbl->height()/2+10,100,100);
    fileInfolbl->setGeometry(pie->width()/2,pie->height()+10,200,300);
    fileInfolbl->show();
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
    loadinglbl->setMovie(movie);
    loadinglbl->show();
    movie->start();
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

//    QThread* thread = new QThread;
//    DirSizeCounter* worker = new DirSizeCounter(path);
//    emit CountDirSize(worker);
//    worker->moveToThread(thread);
//    connect(worker,SIGNAL(SizeCounted(qint64)),this,SLOT(ShowDirSizelabel(qint64)));
//    connect(thread, SIGNAL (started()), worker, SLOT (process()));
//    connect(worker, SIGNAL (finished()), thread, SLOT (quit()));
//    connect(worker, SIGNAL (finished()), worker, SLOT (deleteLater()));
//    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
//    thread->start();
    pie->updatePie(fileInfoList, dir.dirName());

}

void MainWindow::ShowFileInfo(bool hovered, QString fileName)
{
    QString absPath = path + "/" +fileName;
    QFileInfo fileInfo(absPath);
    fileInfolbl->setText(fileName +"\n" + DirSizeCounter::sizeHuman(pie->listOfFileSizes->value(fileName)));
    hovered?fileInfolbl->setVisible(true):fileInfolbl->setVisible(false);
}
void MainWindow::on_btnback_clicked()
{
    if (!pathStack->isEmpty()){
        path = pathStack->pop();
        updateWindow(path);
    }

}
void MainWindow::ShowDirSizelabel(qint64 size)
{
    dirSizelbl->setText(DirSizeCounter::sizeHuman(size));
}
void MainWindow::StopLoadingAnimation(){
    movie->stop();
    loadinglbl->setVisible(false);
}
