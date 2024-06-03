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
    int cluster_id = getSelectedClusterId();
    if (ui->upvoteRadioButton->isChecked()) {
        loadAndDisplayData(cluster_id, true);
    } else if (ui->repostRadioButton->isChecked()) {
        loadAndDisplayData(cluster_id, false);
    }
}

int infowindow::getSelectedClusterId()
{
    int index = ui->clusterComboBox->currentIndex();
    return index ;  // Assuming cluster IDs start from 1
}

void infowindow::loadAndDisplayData(int cluster_id, bool showFirst10)
{
    QFile file(":/tsne.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open the file!";
        return;
    }

    QTextStream in(&file);
    QVector<QPair<QString, double>> comments;

    QRegularExpression re("(\\d+),(\\d+\\.\\d+),\"(.*)\"");

    while (!in.atEnd()) {
        QString line = in.readLine();
        QRegularExpressionMatch match = re.match(line);
        if (!match.hasMatch()) {
            qDebug() << "Skipping invalid line:" << line;
            continue;
        }

        int id = match.captured(1).toInt();
        double distance = match.captured(2).toDouble();
        QString comment = match.captured(3);

        if (id == cluster_id) {
            comments.append(qMakePair(comment, distance));
        }
        if (comments.size() ==25){
            break;
        }
    }

    std::sort(comments.begin(), comments.end(), [](const QPair<QString, double> &a, const QPair<QString, double> &b) {
        return a.second < b.second;
    });

    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Comment");
    ui->tableWidget->setColumnWidth(0, 500);

    int start = showFirst10 ? 0 : 10;
    int end = qMin(start + 10, comments.size());

    for (int i = start; i < end; ++i) {
        QTableWidgetItem *commentItem = new QTableWidgetItem(comments[i].first);
        commentItem->setFlags(commentItem->flags() & ~Qt::ItemIsEditable); // Make the item read-only

        ui->tableWidget->setItem(i - start, 0, commentItem);
    }

    file.close();
}
