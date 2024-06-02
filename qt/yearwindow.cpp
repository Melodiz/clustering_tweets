#include "yearwindow.h"
#include "ui_yearwindow.h"
#include "yearwindow.h"
#include <QComboBox>
#include <QPushButton>
#include <QTextBrowser>
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDir>

yearwindow::yearwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::layout)
{
    ui->setupUi(this);
    setWindowTitle("Year Window");

}

yearwindow::~yearwindow()
{
    delete ui;
}


void yearwindow::on_showHtmlButton_clicked()
{
    qDebug() << "showHtmlForYear start";

    if (!ui->yearComboBox) {
        qWarning() << "yearComboBox is null";
        return;
    }

    if (!ui->htmlViewer) {
        qWarning() << "htmlViewer is null";
        return;
    }

    QString selectedYear = ui->yearComboBox->currentText();
    qDebug() << "Selected year:" << selectedYear;

    if (selectedYear.isEmpty()) {
        qWarning() << "Selected year is empty";
        QMessageBox::warning(this, "Error", "Please select a valid year.");
        return;
    }

    QString htmlFilePath = getHtmlFilePath(selectedYear);
    qDebug() << "HTML file path:" << htmlFilePath;

    QFile file(htmlFilePath);
    if (!file.exists()) {
        QMessageBox::warning(this, "Error", "HTML file for the selected year does not exist.");
        qWarning() << "HTML file does not exist:" << htmlFilePath;
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not open HTML file for the selected year.");
        qWarning() << "Failed to open file:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    QString htmlContent = in.readAll();
    file.close();

    qDebug() << "HTML Content: " << htmlContent;

    ui->htmlViewer->setHtml(htmlContent);
    qDebug() << "showHtmlForYear end";
}

QString yearwindow::getHtmlFilePath(const QString &year) {
    QString path = QString(":/year_maps/%1.html").arg(year);
    qDebug() << "HTML file path:" << path;
    return path;
}
