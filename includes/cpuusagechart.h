#pragma once

#include <QChartView>
#include <QLineSeries>
#include <QTimer>
#include <QtCharts>
#include <fstream>
#include <vector>
#include <sstream>

QT_USE_NAMESPACE

    class CpuUsageChart : public QChartView {
    Q_OBJECT

public:
    CpuUsageChart(QWidget *parent = nullptr);

private slots:
    void updateChart();

private:
    QLineSeries *series;
    QTimer *timer;
    int timeStep;
    std::vector<long> prevCpuData;

    double getCpuUsage();
};
