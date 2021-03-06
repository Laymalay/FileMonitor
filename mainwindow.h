#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QMainWindow>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QLabel>
#include <QThread>
#include <QApplication>
#include <QFileSystemModel>
#include <QMovie>
#include <QFileDialog>
#include <QFileSystemWatcher>
#include "directorypie.h"
#include "worker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    DirectoryPie *pie;
    ~MainWindow();
public slots:
    void ShowDirSizelabel(qint64 size);
    void StopLoadingAnimation();
private slots:
    void on_btnBrowse_clicked();
    void onSliceClicked(QString fileName);
    void updateWindow(QString path);
    void ShowFileInfo(bool hovered, QString fileName);
    void on_btnback_clicked();

signals:
    void AbortWorker();
    void CountDirSize(DirSizeCounter* counter);
private:
    Ui::MainWindow *ui;
    QString path;
    QMovie *movie;
    QLabel *fileInfolbl, *dirSizelbl, *loadinglbl;
    QStack<QString> *pathStack;
    QColor getRandomColor();
    QColor getNewTone(int i, QColor color);
};

#endif // MAINWINDOW_H
