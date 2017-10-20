#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QMainWindow>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QFileDialog>
#include <QFileSystemWatcher>
#include "directorypie.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnBrowse_clicked();
    void onSliceClicked(QString fileName);
    void updateWindow(QString path);
    void ShowFileInfo(bool hovered, QString fileName);
    void on_btnback_clicked();

private:
    Ui::MainWindow *ui;
    QString path;
    DirectoryPie *pie;
    QStack<QString> *pathStack;
};

#endif // MAINWINDOW_H
