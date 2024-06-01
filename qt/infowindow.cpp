#include "infowindow.h"
#include "ui_infowindow.h"

InfoWindow::InfoWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InfoWindow)
{
    ui->setupUi(this);
    setWindowTitle("Info Window");
}

InfoWindow::~InfoWindow()
{
    delete ui;
}


void InfoWindow::on_infoShowButton_clicked()
{

}

