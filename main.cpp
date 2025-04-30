#include "includes/cpuusagechart.h"
#include "includes/ramusagechart.h"
#include "includes/wifisignalchart.h"
#include <QApplication>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QWidget window;
  window.setWindowTitle("System Monitor");

  CpuUsageChart cpuChart;
  RamUsageChart ramChart;
  WifiSignalChart wifiChart;

  // 1.  Use a QGridLayout for the main layout
  QGridLayout *mainLayout = new QGridLayout;

  // 2. Add charts to the grid.  You can control the row/column placement
  //    and how much space they take up (rowspan, colspan)
  mainLayout->addWidget(&cpuChart, 0, 0, 1, 1); // CPU Chart in top-left
  mainLayout->addWidget(&ramChart, 0, 1, 1, 1); // RAM Chart in top-right
  mainLayout->addWidget(&wifiChart, 1, 0, 1,
                        2); // Wifi Chart in bottom, spanning both columns

  // Create a QWidget to hold the mainLayout
  QWidget *centralWidget = new QWidget;
  centralWidget->setLayout(mainLayout);

  // 3. Use a QScrollArea
  QScrollArea *scrollArea = new QScrollArea;
  scrollArea->setWidget(centralWidget); // Set the central widget
  scrollArea->setWidgetResizable(
      true); // Important: Make the scroll area resizable

  // Set the QScrollArea as the main layout of the window
  QVBoxLayout *windowLayout =
      new QVBoxLayout(&window); // use the window as parent.
  windowLayout->addWidget(scrollArea);

  window.resize(800, 600);
  window.show();

  return a.exec();
}
