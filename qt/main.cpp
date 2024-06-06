#include "mainwindow.h"

#include <QApplication>

#include <QWebEngineView>
#include <QVBoxLayout>
#include <QWidget>
#include <QIcon>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":/photos/chat.png"));

    MainWindow w;
    w.show();
    return a.exec();



}
