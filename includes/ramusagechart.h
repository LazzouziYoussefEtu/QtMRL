#pragma once

#include <QWidget>
#include <QTimer>
#include <QChartView>
#include <QLineSeries>
#include <QtCharts>

QT_USE_NAMESPACE

    class RamUsageChart : public QChartView {
    Q_OBJECT

public:
    RamUsageChart(QWidget *parent = nullptr);

private slots:
    void updateChart();

private:
    QLineSeries *series;
    QTimer *timer;
    int timeStep;
};
