#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtCore/QThread>
#include <QtCore/QDebug>
#include <QtGui/QPainter>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#include "RectMatrix.h"
#include "RectMatrixLogic.h"

#include "AVRProcessor.h"
#include "RegulatedAVRProcessor.h"
#include "RRAVRProcessor.h"

int main(int argc, char** argv){

  QApplication app(argc, argv);
  
  AVRProcessor* cpu = new RegulatedAVRProcessor;
  QThread* cpu_thread = new QThread;
  cpu->moveToThread(cpu_thread);

  QObject::connect(cpu_thread, &QThread::started, cpu, &AVRProcessor::run);

  QObject::connect(cpu, &AVRProcessor::finished, cpu_thread, &QThread::quit);
  QObject::connect(cpu, &AVRProcessor::finished, cpu, &AVRProcessor::deleteLater);
  QObject::connect(cpu, &AVRProcessor::finished, cpu_thread, &QThread::deleteLater);

  RectMatrix* matrix_widget = new RectMatrix(25);
  RectMatrixLogic* matrix_logic = new RectMatrixLogic();

  matrix_logic->init();

  QObject::connect(cpu, &AVRProcessor::loaded, matrix_logic, &RectMatrixLogic::attach);
  QObject::connect(matrix_logic, &RectMatrixLogic::setRow, matrix_widget, &RectMatrix::setRow);
  QObject::connect(matrix_logic, &RectMatrixLogic::setCol, matrix_widget, &RectMatrix::setCol);

  matrix_widget->show();

  cpu->load("src/avr/main.axf", "atmega64", 8000000);

  cpu_thread->start();

  return app.exec();
  
}
