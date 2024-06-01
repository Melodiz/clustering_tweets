#include "searchwindow.h"
#include "ui_searchwindow.h"
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QLabel>
#include <QString>
#include <QFile>
#include <QTextStream>



SearchWindow::SearchWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SearchWindow)
{
    ui->setupUi(this);
    setWindowTitle("Search Window");
}

SearchWindow::~SearchWindow()
{
    delete ui;
}

void SearchWindow::on_searchShowButton_clicked()
{
    QString comment = ui->comment->text();

    QFile file("newdata.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    in.readLine();  // Skip header row
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        if (fields[1].contains(comment, Qt::CaseInsensitive)) {
            resultList->addItem(fields[1]);
        }
    }

}

