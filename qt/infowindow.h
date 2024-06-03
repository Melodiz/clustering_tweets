#ifndef infowindow_H
#define infowindow_H

#include <QWidget>
#include <QVector>
#include <QPair>
#include <QDialog>
#include <QRadioButton>

namespace Ui {
class infowindow;
}

class infowindow : public QDialog
{
    Q_OBJECT

public:
    explicit infowindow(QWidget *parent = nullptr);
    ~infowindow();

private slots:
    void on_showButton_clicked();

private:
    Ui::infowindow *ui;
    QRadioButton *upvoteRadioButton;
    int getSelectedClusterId();
    void loadAndDisplayData(int cluster_id);
};

#endif // infowindow_H
