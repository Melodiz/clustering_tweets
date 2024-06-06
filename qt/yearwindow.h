#ifndef YEARWINDOW_H
#define YEARWINDOW_H

#include <QDialog>

#include <QComboBox>
#include <QTableWidget>
#include <QLabel>
#include <QPushButton>
#include <QMap>
#include <QVector>
#include <QPair>

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
    QLabel *imageLabel;
    QTableWidget *tableWidget;

    QMap<int, QVector<QPair<int, int>>> yearClusterData;
    QMap<int, QString> clusterNames;

    void loadData();
    void updateTableAndImage(int year);
    void initializeClusterNames();
};

#endif // YEARWINDOW_H

