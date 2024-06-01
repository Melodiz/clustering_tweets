#include "yearwindow.h"
#include "ui_yearwindow.h"

YearWindow::YearWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::YearWindow)
{
    ui->setupUi(this);
    setWindowTitle("Year Window");
}

YearWindow::~YearWindow()
{
    delete ui;
}

void YearWindow::on_yearShowButton_clicked()
{
    QString year = ui->year->text();
}

