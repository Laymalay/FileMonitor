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
    void NotifyChanges(const QString &path);
    void onSliceClicked(QString path);
    void ShowFileInfo(bool hovered, QString fileName);

private:
    Ui::MainWindow *ui;
    QFileSystemWatcher *watcher;
    QString path;
    DirectoryPie *pie;
};

#endif // MAINWINDOW_H
