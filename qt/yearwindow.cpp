#include "yearwindow.h"
#include "ui_yearwindow.h"
#include <QFile>
#include <QTextStream>
#include <QHeaderView>
#include <QMessageBox>
#include <QPixmap>
#include <QDir>
#include <QDateTime>
#include <algorithm>
#include <QDebug>

yearwindow::yearwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::layout)
{
    ui->setupUi(this);
    setWindowTitle("Year Window");
    loadData();
    initializeClusterNames();

}

yearwindow::~yearwindow()

{
    delete ui;
}

void yearwindow::initializeClusterNames()
{
    clusterNames.insert(0, "Skepticism");
    clusterNames.insert(1, "Fatalism");
    clusterNames.insert(2, "Politics");
    clusterNames.insert(3, "Natural Disasters");
    clusterNames.insert(4, "Renewable Energy");
    clusterNames.insert(5, "Wildlife");
    clusterNames.insert(6, "Agriculture");
    clusterNames.insert(7, "Health");
    clusterNames.insert(8, "Technology");
    clusterNames.insert(9, "Economics");
    clusterNames.insert(10, "Activism");
    clusterNames.insert(11, "Education");
    clusterNames.insert(12, "Policy");
    clusterNames.insert(13, "Transportation");
    clusterNames.insert(14, "Personal Responsibility");
    clusterNames.insert(15, "Media");
    clusterNames.insert(16, "Water Resources");
    clusterNames.insert(17, "Urban Planning");
    clusterNames.insert(18, "Historical Context");
    clusterNames.insert(19, "International Relations");
    clusterNames.insert(20, "Indigenous Perspectives");
    clusterNames.insert(21, "Gender");
    clusterNames.insert(22, "Youth");
    clusterNames.insert(23, "Art");
    clusterNames.insert(24, "Religion");
}

void yearwindow::loadData()
{
    QFile file(":/smalldata.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Error", "Could not open CSV file.");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        if (fields.size() < 3)
            continue;

        int year = static_cast<int>(fields[0].toFloat());
        int clusterId = fields[2].toInt();



        yearClusterData[year].append(qMakePair(clusterId, 1));
    }
    file.close();

    for (auto &yearClusters : yearClusterData)
    {
        QMap<int, int> clusterCounts;
        for (const auto &cluster : yearClusters)
        {
            clusterCounts[cluster.first] += cluster.second;
        }
        yearClusters.clear();
        for (auto it = clusterCounts.begin(); it != clusterCounts.end(); ++it)
        {
            yearClusters.append(qMakePair(it.key(), it.value()));
        }
    }

    for (auto it = yearClusterData.constBegin(); it != yearClusterData.constEnd(); ++it)
    {
        qDebug() << "Year:" << it.key() << "Clusters:" << it.value();
    }
}

void yearwindow::on_showHtmlButton_clicked()
{
    QString yearStr = ui->yearComboBox->currentText();
    int year = yearStr.toInt();
    updateTableAndImage(year);
}

void yearwindow::updateTableAndImage(int year)
{
    if (!yearClusterData.contains(year) || yearClusterData[year].isEmpty())
    {
        ui->tableWidget->setRowCount(0);
        ui->imageLabel->clear();
        QMessageBox::warning(this, "Data not found", QString("No data found for year %1").arg(year));
        return;
    }

    auto clusters = yearClusterData[year];
    std::sort(clusters.begin(), clusters.end(), [](const auto &a, const auto &b) {
        return a.second > b.second;
    });

    int rowCount = std::min(5, static_cast<int>(clusters.size()));
    ui->tableWidget->setRowCount(rowCount);
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setColumnWidth(0, 600);
    ui->tableWidget->setHorizontalHeaderLabels({"Most popular clusters"});

    for (int i = 0; i < rowCount; ++i)
    {
        QString clusterName = clusterNames.value(clusters[i].first, QString::number(clusters[i].first));
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(clusterName));
    }

    QString imagePath = QString(":/photos/%1.png").arg(year);
    if (QFile::exists(imagePath))
    {
        QPixmap pixmap(imagePath);

        ui->imageLabel->setPixmap(pixmap.scaled(width(), height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->imageLabel->setScaledContents(true);
    }
    else
    {
        ui->imageLabel->clear();
        QMessageBox::warning(this, "Image not found", QString("No image found for year %1").arg(year));
    }
}
