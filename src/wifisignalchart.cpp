
#include "../includes/wifisignalchart.h"
#include <QDebug>
#include <QFont>
#include <QGraphicsTextItem>
#include <QPainter>
#include <QProcess>
#include <QRegularExpression>
#include <QValueAxis>

WifiSignalChart::WifiSignalChart(QWidget *parent)
    : QChartView(parent), series(new QLineSeries), timer(new QTimer(this)),
      timeStep(0), axisX(new QValueAxis), axisY(new QValueAxis),
      ssidTextItem(nullptr) {
  QChart *chart = new QChart();
  chart->addSeries(series);
  QString ssid = getWifiSSID(wifiInterface);
  qDebug() << "Detected SSID:" << ssid;

  if (!ssid.isEmpty()) {
    chart->setTitle("WiFi \"" + ssid + "\" Signal Strength (dBm)");
  } else {
    chart->setTitle("WiFi Signal Strength (dBm)");
  }

  chart->legend()->hide();
  chart->setAnimationOptions(QChart::NoAnimation);
  this->setChart(chart);
  this->setRenderHint(QPainter::Antialiasing);

  axisX->setTitleText("Time");
  axisX->setLabelFormat("%d");
  axisX->setTickCount(7);
  chart->addAxis(axisX, Qt::AlignBottom);
  series->attachAxis(axisX);

  axisY->setTitleText("Signale (dBm)");
  axisY->setRange(-100, -30);
  axisY->setLabelFormat("%d");
  chart->addAxis(axisY, Qt::AlignLeft);
  series->attachAxis(axisY);

  wifiInterface = detectWifiInterface();
  qDebug() << "WiFi Interface:" << wifiInterface;

  ssidTextItem = new QGraphicsTextItem(chart);
  ssidTextItem->setPlainText("SSID: " + ssid);
  ssidTextItem->setFont(QFont("Arial", 10));
  ssidTextItem->setDefaultTextColor(QColor(Qt::white));
  ssidTextItem->setPos(10, 20);

  ssidTextItem->show();

  connect(timer, &QTimer::timeout, this, &WifiSignalChart::updateChart);
  timer->start(250);
}

QString WifiSignalChart::detectWifiInterface() {
  QProcess proc;
  proc.start("iwconfig");
  proc.waitForFinished();
  QString output = proc.readAllStandardOutput();
  qDebug() << "iwconfig output:\n" << output;

  QRegularExpression regex(R"((\w+)\s+IEEE 802\.11)");
  QRegularExpressionMatchIterator i = regex.globalMatch(output);
  while (i.hasNext()) {
    QRegularExpressionMatch match = i.next();
    return match.captured(1);
  }
  return QString();
}

QString WifiSignalChart::getWifiSSID(const QString &interface) {
  if (interface.isEmpty())
    return QString();

  QProcess proc;
  proc.start("iwconfig", QStringList() << interface);
  proc.waitForFinished();
  QString output = proc.readAllStandardOutput();
  qDebug() << "SSID output:\n" << output;

  // Match ESSID:"something"
  QRegularExpression regex(R"(ESSID:\"([^\"]*)\")");
  QRegularExpressionMatch match = regex.match(output);

  if (match.hasMatch()) {
    QString ssid = match.captured(1).trimmed();
    return ssid.isEmpty() ? QString() : ssid;
  }

  return QString();
}

int WifiSignalChart::getSignalStrength(const QString &interface) {
  if (interface.isEmpty())
    return -100;

  QProcess proc;
  proc.start("iwconfig", QStringList() << interface);
  proc.waitForFinished();
  QString output = proc.readAllStandardOutput();

  QRegularExpression regex(R"(Signal level=([-]?\d+)\s*dBm)");
  QRegularExpressionMatch match = regex.match(output);

  if (match.hasMatch())
    return match.captured(1).toInt();

  return -100; // Fallback if no match
}

void WifiSignalChart::updateChart() {
  int signal = getSignalStrength(wifiInterface);
  qDebug() << "Time:" << timeStep << "Signal Strength:" << signal;

  series->append(timeStep, signal);

  const int windowSize = 60;
  if (series->count() > windowSize)
    series->removePoints(0, series->count() - windowSize);

  axisX->setRange(timeStep - windowSize + 1, timeStep + 1);
  timeStep++;
  QString ssid = getWifiSSID(wifiInterface);
  if (ssidTextItem) {
    ssidTextItem->setPlainText("SSID: " + ssid);
  }
}
