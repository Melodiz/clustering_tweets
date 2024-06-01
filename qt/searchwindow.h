#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QDialog>
#include <QListWidget>

namespace Ui {
class SearchWindow;
}

class SearchWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SearchWindow(QWidget *parent = nullptr);
    ~SearchWindow();

private slots:
    void on_searchShowButton_clicked();



private:
    Ui::SearchWindow *ui;
    QListWidget *resultList;
};

#endif // SEARCHWINDOW_H
