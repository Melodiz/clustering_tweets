#ifndef YEARWINDOW_H
#define YEARWINDOW_H

#include <QDialog>
#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QTextBrowser>
#include "searchwindow.h"
#include <QWebEngineView>

namespace Ui {
class layout;
}

class yearwindow : public QDialog
{
    Q_OBJECT

public:
    explicit yearwindow(QWidget *parent = nullptr);
    ~yearwindow();

private slots:

    void on_showHtmlButton_clicked();


private:
    Ui::layout *ui;

    QComboBox *yearComboBox;
    QPushButton *showHtmlButton;
    QTextBrowser *htmlViewer;
    QString getHtmlFilePath(const QString &year);
};

#endif // YEARWINDOW_H

