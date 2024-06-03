#include "infowindow.h"
#include "ui_infowindow.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QListWidgetItem>
#include <algorithm>

infowindow::infowindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::infowindow)

{
    ui->setupUi(this);
    setWindowTitle("Info Window");
}


infowindow::~infowindow()
{
    delete ui;
}

void infowindow::on_showButton_clicked()
{
    if (ui->upvoteRadioButton->isChecked()) {
        int cluster_id = getSelectedClusterId();
        loadAndDisplayData(cluster_id);
    }
}

int infowindow::getSelectedClusterId()
{
    int index = ui->clusterComboBox->currentIndex();
    return index + 1;  // Assuming cluster IDs start from 1
}

void infowindow::loadAndDisplayData(int cluster_id)
{
    QFile file(":/TSNEClustered.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open the file!";
        return;
    }

    QTextStream in(&file);
    QVector<QPair<QString, double>> comments;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        if (fields.size() != 3) {
            continue;
        }

        int id = fields[0].toInt();
        double distance = fields[1].toDouble();
        QString comment = fields[2];

        if (id == cluster_id) {
            comments.append(qMakePair(comment, distance));
        }
    }

    std::sort(comments.begin(), comments.end(), [](const QPair<QString, double> &a, const QPair<QString, double> &b) {
        return a.second < b.second;
    });

    ui->listWidget->clear(); // Clear the previous list

    for (int i = 0; i < 10 && i < comments.size(); ++i) {
        QListWidgetItem *item = new QListWidgetItem(comments[i].first + " (Distance: " + QString::number(comments[i].second) + ")");
        item->setFlags(item->flags() & ~Qt::ItemIsEditable); // Make the item read-only
        ui->listWidget->addItem(item);
    }

    file.close();
}
