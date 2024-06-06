#ifndef searchwindow_H
#define searchwindow_H

#include <QDialog>

namespace Ui {
class searchwindow;
}

class searchwindow : public QDialog
{
    Q_OBJECT

public:
    explicit searchwindow(QWidget *parent = nullptr);
    ~searchwindow();

private slots:
    void on_searchButton_clicked();

private:
    Ui::searchwindow *ui;
    void loadAndDisplayData(const QString &searchTerm);
};

#endif // searchwindow_H
