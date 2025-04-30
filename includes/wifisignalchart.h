#pragma once

#include <QTimer>
#include <QValueAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QGraphicsTextItem>
QT_USE_NAMESPACE

    class WifiSignalChart : public QChartView {
    Q_OBJECT

public:
    explicit WifiSignalChart(QWidget *parent = nullptr);

private:
    QLineSeries *series;
    QTimer *timer;
    int timeStep;
    QString wifiInterface;
    QString detectWifiInterface();
    QValueAxis *axisX;
    QValueAxis *axisY;
    int getSignalStrength(const QString &interface);
    QString getWifiSSID(const QString &interface);
    void updateChart();

    QGraphicsTextItem *ssidTextItem;
};
