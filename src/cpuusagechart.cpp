#include "../includes/cpuusagechart.h"

CpuUsageChart::CpuUsageChart(QWidget *parent)
    : QChartView(parent), series(new QSplineSeries()), timer(new QTimer(this)),
      timeStep(0) {
  QChart *chart = new QChart();
  chart->legend()->hide();
  chart->addSeries(series);
  chart->createDefaultAxes();
  chart->setTitle("Real-time CPU Usage");

  this->setChart(chart);
  this->setRenderHint(QPainter::Antialiasing);

  connect(timer, &QTimer::timeout, this, &CpuUsageChart::updateChart);
  timer->start(250); 
}

void CpuUsageChart::updateChart() {
  double usage = getCpuUsage();
  series->append(timeStep++, usage);

  if (series->count() > 60) {
    series->removePoints(0, series->count() - 60);
  }

  chart()->axisX()->setRange(timeStep - 60, timeStep);
  chart()->axisY()->setRange(0, 100);
}

double CpuUsageChart::getCpuUsage() {
  std::ifstream stat("/proc/stat");
  std::string line;
  std::getline(stat, line);

  std::stringstream ss(line.substr(5));
  std::vector<long> cpuData;
  long value;
  while (ss >> value) {
    cpuData.push_back(value);
  }

  if (prevCpuData.empty()) {
    prevCpuData = cpuData;
    return 0.0;
  }

  long prevIdle = prevCpuData[3] + prevCpuData[4];
  long idle = cpuData[3] + cpuData[4];

  long prevNonIdle = prevCpuData[0] + prevCpuData[1] + prevCpuData[2] +
                     prevCpuData[5] + prevCpuData[6] + prevCpuData[7];
  long nonIdle = cpuData[0] + cpuData[1] + cpuData[2] + cpuData[5] +
                 cpuData[6] + cpuData[7];

  long prevTotal = prevIdle + prevNonIdle;
  long total = idle + nonIdle;

  long totalDiff = total - prevTotal;
  long idleDiff = idle - prevIdle;

  prevCpuData = cpuData;

  if (totalDiff == 0)
    return 0.0;

  return static_cast<double>(totalDiff - idleDiff) / totalDiff * 100.0;
}
