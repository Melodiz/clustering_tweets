#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "yearwindow.h"
#include "searchwindow.h"
#include "infowindow.h"
#include <QListWidget>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_yearButton_clicked();

    void on_searchButton_clicked();

    void on_infoButton_clicked();

private:
    Ui::MainWindow *ui;
    yearwindow *Ywindow;
    infowindow *Iwindow;
    searchwindow *Swindow;


};
#endif // MAINWINDOW_H
