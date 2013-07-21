#include "mainwindow.h"

#include <QtWidgets/QApplication>
#include <QtCore/QThread>
#include <QtCore/QDebug>

#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QFileDialog>

#include <stdio.h>
#include <stdlib.h>

#include "AVRProcessor.h"
#include "RegulatedAVRProcessor.h"
#include "RRAVRProcessor.h"
#include "HybridAVRProcessor.h"

MainWindow::MainWindow( QWidget* parent ) :
  QMainWindow( parent ),
  ui( new Ui::MainWindow )
{

  ui->setupUi( this );

  //TODO install message handler to redirect qDebug | QTextBrowser
  this->initSettings();

  this->initComponents();

  this->connectActions(ui);
}

MainWindow::~MainWindow(){}

void MainWindow::initSettings(void){

  //TODO init QSettings
  this->resize(640,480);

  QCoreApplication::setApplicationName("ESS");
  QCoreApplication::setApplicationVersion("1.0");

  //QCoreApplication::setOrganizationDomain("ESS");
  //QCoreApplication::setOrganizationName("ESS");

}

void MainWindow::initComponents(void){

  this->cpu = new RegulatedAVRProcessor(QString("atmega64"), 8000000);

  this->cpuThread = new QThread;

  this->cpu->moveToThread(cpuThread);

  QObject::connect(cpuThread, &QThread::started, cpu, &AVRProcessor::run);

  QObject::connect(cpu, &AVRProcessor::stopped, cpuThread, &QThread::quit);

  this->filename = QString("src/avr/main.axf");

  this->cpu->loadFirmware(this->filename);
}

void MainWindow::connectActions(Ui::MainWindow* ui){

  connect(ui->actionAbout_Qt,SIGNAL(triggered()), qApp, SLOT(aboutQt()));
  connect(ui->actionClose,SIGNAL(triggered()), qApp, SLOT(quit()));

  connect(ui->actionStart,SIGNAL(triggered()), this, SLOT(startSimulation()));
  connect(ui->actionPause,SIGNAL(triggered()), this, SLOT(stopSimulation()));
  connect(ui->actionStop,SIGNAL(triggered()), this, SLOT(stopSimulation()));

  connect(ui->actionLoad_Firmware,SIGNAL(triggered()), this, SLOT(loadFirmware()));
  connect(ui->actionReload_Firmware,SIGNAL(triggered()), this, SLOT(reloadFirmware()));

  QComboBox* comboBox = new QComboBox(this);

  comboBox->addItem(QString("atmega64"));
  comboBox->addItem(QString("atmega128"));

  ui->toolBar->addWidget(comboBox);

  QSpinBox* spinBox = new QSpinBox(this);

  spinBox->setMaximum(100000000);
  spinBox->setMinimum(0);

  spinBox->setValue(8000000);
  spinBox->setSuffix(QString(" Hz"));

  ui->toolBar->addWidget(spinBox);
}

void MainWindow::startSimulation(void){

  if(this->filename.isEmpty()){
    return;
  }

  this->cpuThread->start();
}

void MainWindow::stopSimulation() {

  if(this->filename.isEmpty()){
    return;
  }

  this->cpu->stop();

  this->cpuThread->quit();

  this->cpuThread->wait();

}

void MainWindow::loadFirmware(void){

  this->stopSimulation();

  this->filename = QFileDialog::getOpenFileName(this, tr("Load Firmware") );

  if( !this->filename.isEmpty() ){
    this->cpu->loadFirmware(this->filename);
  }

}

void MainWindow::reloadFirmware(void){

  if(this->filename.isEmpty()){
    return;
  }

  this->stopSimulation();

  this->cpu->loadFirmware(this->filename);

  this->cpuThread->start();

}