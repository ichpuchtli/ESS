/**
 * \file mainwindow.cpp
 * \brief the main class controlling simulations and the main window
 * \author Sam Macpherson
 *
 * Copyright 2013  Sam Macpherson <sam.mack91@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "mainwindow.h"

#include <QtCore/QThread>
#include <QtCore/QDebug>
#include <QtCore/QJsonObject>
#include <QtCore/QPluginLoader>

#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

// Plugin Classes
#include "AbstractPeripheralFactory.h"
#include "AbstractPeripheralLogic.h"
#include "AbstractPeripheralWidget.h"
#include "PinFactory.h"

// Processeors
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

  this->connectActions();
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

  PinFactory* pinFactory = new PinFactory(cpu->getAVR(), cpuThread);

  this->filename = QString("src/avr/main.axf");

  this->cpu->loadFirmware(this->filename);

  this->pluginManager = new PluginManager(cpuThread, ui->mdiArea, cpu->getAVR(),pinFactory);

  QDir pluginDirectory(QCoreApplication::applicationDirPath() + "/" + "plugins");

  foreach(const QString& filename, pluginDirectory.entryList(QDir::NoDotAndDotDot | QDir::Files)){
    this->pluginManager->load(pluginDirectory, filename);
  }

  foreach(const QString plugin, this->pluginManager->listPlugins()){
    this->pluginManager->show(plugin);
    this->pluginManager->connect(plugin);
  }

}

void MainWindow::connectActions(void){

  connect(ui->actionAbout_Qt,SIGNAL(triggered()), qApp, SLOT(aboutQt()));
  connect(ui->actionClose,SIGNAL(triggered()), qApp, SLOT(quit()));

  connect(ui->actionAbout_ESS, SIGNAL(triggered()), this, SLOT(aboutESS()));
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

  spinBox->setMaximum(10000000);
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

void MainWindow::aboutESS(void){

  QMessageBox::about(this, QString("About ESS"),
                     QString("The Embedded System Simulator,  "
                             "<a href=\"http://www.github.com/ichpuchtli/ess\">"
                             "github.com/ichpuchtli/ess</a>"));

}
