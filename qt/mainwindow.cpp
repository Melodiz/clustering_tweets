#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "yearwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Main Window");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_yearButton_clicked()
{

    Ywindow = new yearwindow(this);

    Ywindow -> show();
}


void MainWindow::on_searchButton_clicked()
{

    Swindow = new searchwindow(this);

    Swindow -> show();
}


void MainWindow::on_infoButton_clicked()
{

    Iwindow = new infowindow(this);

    Iwindow -> show();
}

