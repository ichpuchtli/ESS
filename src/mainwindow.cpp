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

#include <stdio.h>

#include <QtCore/QThread>
#include <QtCore/QDebug>
#include <QtCore/QJsonObject>
#include <QtCore/QPluginLoader>

#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QTextEdit>

#include <QDesktopServices>

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QUrl>

#include <QtCore/QSettings>

#include "AVRIOAdapter.h"

#include "AVRProcessor.h"
#include "RegulatedAVRProcessor.h"
#include "RRAVRProcessor.h"
#include "HybridAVRProcessor.h"


MainWindow::MainWindow( QWidget* parent ) :
  QMainWindow( parent ),
  ui( new Ui::MainWindow )
{

  QCoreApplication::setApplicationName( "simavr-qt" );
  QCoreApplication::setApplicationVersion( "1.0" );

  QCoreApplication::setOrganizationDomain( "ichpuchtli.com" );
  QCoreApplication::setOrganizationName( "ichpuchtli" );

  ui->setupUi( this );

  this->initLogMonitor();

  this->initComponents();

  this->connectActions();

  this->loadSettings();
}

MainWindow::~MainWindow()
{
  saveSettings();
}

void MainWindow::timerEvent( QTimerEvent * e )
{

  ( void ) e;

  QTextStream stream( this->log );

  QString line = stream.readLine();

  while ( !line.isEmpty() ) {

    ui->logViewer->append( line );

    line = stream.readLine();

    ui->logViewer->moveCursor( QTextCursor::End );
  }

  if(this->cpuThread->isRunning()){
    statusBar()->showMessage(QString("Running: %1").arg(this->cpu->getFrequency()));
  }

}

void MainWindow::initComponents( void )
{

  this->cpu = new RegulatedAVRProcessor( QString( "atmega64" ), 8000000 );

  this->cpuThread = new QThread;
  this->cpu->moveToThread( cpuThread );

  QObject::connect( cpuThread, &QThread::started, cpu, &AVRProcessor::run );
  QObject::connect( cpu, &AVRProcessor::stopped, cpuThread, &QThread::quit );

  //TODO connect SIGNAL(deleteLater) to all objects allocated in this method
  AVRIOAdapter* io = new AVRIOAdapter( cpu->getAVR(), cpuThread );

  this->pluginManager = new PluginManager( io, ui->mdiArea );

  connect( this->cpu, SIGNAL( RESET() ), &io->RESET(), SIGNAL( risingEdge() ),
           Qt::DirectConnection );

  QDir pluginDirectory( QCoreApplication::applicationDirPath() + "/" +
                        "plugins" );

  foreach( const QString & filename,
           pluginDirectory.entryList( QDir::NoDotAndDotDot | QDir::Files ) ) {
    this->pluginManager->load( pluginDirectory, filename );
  }

  foreach( const QString plugin, this->pluginManager->listPlugins() ) {
    ui->netManager->addPlugin( plugin, pluginManager->listPluginNets( plugin ) );
  }


  connect( ui->netManager, &NetManager::netChanged, pluginManager,
           &PluginManager::connectPluginNets );

  connect( ui->netManager, &NetManager::pluginDisabled, pluginManager,
           &PluginManager::disconnect );
  connect( ui->netManager, &NetManager::pluginDisabled, pluginManager,
           &PluginManager::hide );

  connect( ui->netManager, &NetManager::pluginEnabled, pluginManager,
           &PluginManager::connect );
  connect( ui->netManager, &NetManager::pluginEnabled, pluginManager,
           &PluginManager::show );


}

void MainWindow::connectActions( void )
{

  connect( ui->actionAbout_Qt, SIGNAL( triggered() ), qApp, SLOT( aboutQt() ) );

  connect( ui->actionClose, SIGNAL( triggered() ), qApp, SLOT( quit() ) );

  connect( ui->actionAbout_ESS, SIGNAL( triggered() ), this, SLOT( aboutESS() ) );
  connect( ui->actionESS_Help, SIGNAL( triggered() ), this,
           SLOT( helpWindow() ) );
  connect( ui->actionStart, SIGNAL( triggered() ), this,
           SLOT( startSimulation() ) );

  connect( ui->actionPause, SIGNAL( triggered() ), this,
           SLOT( pauseSimulation() ) );

  connect( ui->actionStop, SIGNAL( triggered() ), this,
           SLOT( stopSimulation() ) );

  connect( ui->actionLoad_Firmware, SIGNAL( triggered() ), this,
           SLOT( loadFirmware() ) );
  connect( ui->actionReload_Firmware, SIGNAL( triggered() ), this,
           SLOT( reloadFirmware() ) );

  connect( ui->actionNetManager, SIGNAL( triggered( bool ) ) , this,
           SLOT( showNetList( bool ) ) );

  connect( ui->actionConsole, SIGNAL( triggered( bool ) ) , this,
           SLOT( showConsole( bool ) ) );

}

void MainWindow::startSimulation( void )
{

  if ( this->filename.isEmpty() ) {
    return;
  }

  this->cpu->start();

  if(!this->cpuThread->isRunning()){
    this->cpuThread->start();
  }

  statusBar()->showMessage(QString("Running: %1").arg(this->cpu->getFrequency()));

}

void MainWindow::stopSimulation()
{

  if ( this->filename.isEmpty() ) {
    return;
  }

  this->cpu->stop();

  this->cpuThread->quit();

  this->cpuThread->wait();

  this->cpu->getAVR()->reset(this->cpu->getAVR());

  statusBar()->showMessage("Stopped");
}

void MainWindow::pauseSimulation(){

  if ( this->filename.isEmpty() ) {
    return;
  }

  this->cpu->stop();

  statusBar()->showMessage("Paused");

}

void MainWindow::loadFirmware( void )
{

  this->stopSimulation();

  QString file = QFileDialog::getOpenFileName( this, tr( "Load Firmware" ) );

  if ( !file.isEmpty() ) {
    this->filename = file;
    this->cpu->loadFirmware( file );
  }

  saveSettings();

}

void MainWindow::reloadFirmware( void )
{

  if ( this->filename.isEmpty() ) {
    return;
  }

  this->stopSimulation();

  this->cpu->loadFirmware( this->filename );

  this->startSimulation();

}

void MainWindow::aboutESS( void )
{

  QMessageBox::about( this, QString( "About ESS" ),
                      QString( "The Embedded System Simulator,  "
                               "<a href=\"http://www.github.com/ichpuchtli/ess\">"
                               "github.com/ichpuchtli/ess</a>" ) );

}


void MainWindow::helpWindow()
{
  QDesktopServices::openUrl( QUrl( "http://www.github.com/ichpuchtli/ess" ) );
}

static void message_router( QtMsgType type, const QMessageLogContext& context,
                            const QString& msg )
{

  ( void ) type;
  ( void ) context;

  fprintf( stderr, "%s\n", msg.toLocal8Bit().constData() );

  QFile logfile( "log.txt" );

  logfile.open( QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text );

  QTextStream stream( &logfile );

  stream << msg << endl;

}

void MainWindow::initLogMonitor( void )
{

  this->log = new QFile( "log.txt" );

  this->log->resize( 0 );

  this->log->open( QIODevice::ReadOnly | QIODevice::Text );

  qInstallMessageHandler( message_router );

  this->startTimer( 1000 );

}

void MainWindow::showNetList( bool show )
{
  show ? ui->netManager->show() : ui->netManager->hide();

  QSettings settings;
  settings.setValue( "window/netlist", show );
}

void MainWindow::showConsole( bool show )
{
  show ? ui->logViewer->show() : ui->logViewer->hide();

  QSettings settings;
  settings.setValue( "window/console", show );
}

void MainWindow::loadSettings()
{
  QSettings settings;

  resize( settings.value( "window/size", QSize( 640, 480 ) ).toSize() );
  move( settings.value( "window/pos", QPoint( 50, 50 ) ).toPoint() );

  this->filename = settings.value( "project/filename", QString() ).toString();

  if ( !this->filename.isEmpty() ) {
    this->cpu->loadFirmware( this->filename );
  }

  if ( settings.value( "window/console" , true ) == false){
    ui->logViewer->hide();
    ui->actionConsole->setChecked(false);
  }

  if ( settings.value( "window/netlist" , true ) == false){
    ui->netManager->hide();
    ui->actionNetManager->setChecked(false);
  }

  ui->netManager->loadSettings();
}

void MainWindow::saveSettings()
{
  QSettings settings;

  settings.setValue( "window/size", size() );
  settings.setValue( "window/pos", pos() );

  settings.setValue( "project/filename", this->filename );
}
