#ifndef YEARWINDOW_H
#define YEARWINDOW_H

#include <QDialog>

namespace Ui {
class YearWindow;
}

class YearWindow : public QDialog
{
    Q_OBJECT

public:
    explicit YearWindow(QWidget *parent = nullptr);
    ~YearWindow();

private slots:
    void on_yearShowButton_clicked();

private:
    Ui::YearWindow *ui;
};

#endif // YEARWINDOW_H
