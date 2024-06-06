#include "searchwindow.h"
#include "ui_searchwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QListWidgetItem>


searchwindow::searchwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::searchwindow)

{
    ui->setupUi(this);
    setWindowTitle("Search Window");
}

searchwindow::~searchwindow()
{
    delete ui;
}

void searchwindow::on_searchButton_clicked()
{
    QString searchTerm = ui->searchLineEdit->text();
    loadAndDisplayData(searchTerm);
}

void searchwindow::loadAndDisplayData(const QString &searchTerm)

{
    QFile file(":/smalldata.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open the file!";
        return;
    }

    QTextStream in(&file);
    QVector<QString> comments;

    while (!in.atEnd()) {
        QString line = in.readLine();
        int firstCommaIndex = line.indexOf(',');
        // if (firstCommaIndex == -1) {
        //     qDebug() << "Skipping invalid line:" << line;
        //     continue;
        // }

        QString comment = line.mid(firstCommaIndex + 1); // Capture the comment after the first comma
        if (comment.contains(searchTerm, Qt::CaseInsensitive)) {
            comments.append(comment);
        }
        if (comments.size() >= 30) {
            break;
        }
    }

    file.close();

    qDebug() << "Found comments:" << comments;

    ui->resultsListWidget->clear(); // Clear the previous list
    int i = 0;

    for (const QString &comment : comments) {
        QListWidgetItem *item = new QListWidgetItem(comment);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable); // Make the item read-only
        ui->resultsListWidget->addItem(item);
        qDebug() << i++;
    }

    qDebug() << "Displayed comments in the list widget.";
}
