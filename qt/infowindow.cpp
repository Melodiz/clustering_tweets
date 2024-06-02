#include "infowindow.h"
#include "ui_infowindow.h"

infowindow::infowindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::infowindow)
{
    ui->setupUi(this);
    setWindowTitle("Info Window");
}

infowindow::~infowindow()
{
    delete ui;
}
