#include <QApplication>
#include "cpuusagechart.h"
#include "ramusagechart.h"
#include "wifisignalchart.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    CpuUsageChart chart;
    RamUsageChart ramChart;
    WifiSignalChart wifiChart;
    chart.resize(800, 600);
    ramChart.resize(800, 600);
    chart.show();
    ramChart.show();

    wifiChart.resize(800, 600);
    wifiChart.show();
    return a.exec();
}
