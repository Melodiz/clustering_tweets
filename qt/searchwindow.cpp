#include "searchwindow.h"
#include "ui_searchwindow.h"

searchwindow::searchwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::searchwindow)
{
    ui->setupUi(this);
    setWindowTitle("Search Window");
}

searchwindow::~searchwindow()
{
    delete ui;
}
