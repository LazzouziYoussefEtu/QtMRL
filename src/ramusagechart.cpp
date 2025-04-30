#include "../includes/ramusagechart.h"
#include <fstream>
#include <sstream>
#include <string>

double getRamUsagePercentage() {
  std::ifstream meminfo("/proc/meminfo");
  std::string line;
  long totalMem = 0, freeMem = 0, buffers = 0, cached = 0;

  while (std::getline(meminfo, line)) {
    if (line.find("MemTotal:") == 0) {
      std::stringstream ss(line.substr(10));
      ss >> totalMem;
    } else if (line.find("MemFree:") == 0) {
      std::stringstream ss(line.substr(9));
      ss >> freeMem;
    } else if (line.find("Buffers:") == 0) {
      std::stringstream ss(line.substr(8));
      ss >> buffers;
    } else if (line.find("Cached:") == 0) {
      std::stringstream ss(line.substr(7));
      ss >> cached;
    }
  }

  long usedMem = totalMem - freeMem - buffers - cached;
  return totalMem > 0 ? static_cast<double>(usedMem) / totalMem * 100.0 : 0.0;
}

RamUsageChart::RamUsageChart(QWidget *parent)
    : QChartView(parent), series(new QSplineSeries), timer(new QTimer(this)),
      timeStep(0) {
  QChart *chart = new QChart();
  chart->addSeries(series);
  chart->setTitle("RAM Usage (%)");
  chart->legend()->hide();
  chart->createDefaultAxes();

  this->setChart(chart);
  this->setRenderHint(QPainter::Antialiasing);

  connect(timer, &QTimer::timeout, this, &RamUsageChart::updateChart);
  timer->start(250);
}

void RamUsageChart::updateChart() {
  double usage = getRamUsagePercentage();
  series->append(timeStep++, usage);

  if (series->count() > 60)
    series->removePoints(0, series->count() - 60);

  chart()->axisX()->setRange(timeStep - 60, timeStep);
  chart()->axisY()->setRange(0, 100);
}
