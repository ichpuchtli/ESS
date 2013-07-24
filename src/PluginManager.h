/**
 * \file PluginManager.h
 * \brief An class for managing external plugins
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

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtCore/QThread>
#include <QtCore/QJsonObject>
#include <QtCore/QPluginLoader>
#include <QtCore/QMap>
#include <QtCore/QStringList>
#include <QtCore/QString>

#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMdiSubWindow>

#include "sim_avr.h"
#include "AVRIOAdapter.h"

#include "AbstractPeripheralFactory.h"
#include "AbstractPeripheralLogic.h"
#include "AbstractPeripheralWidget.h"


/**
 * \brief An class for managing external plugins
 */
class PluginManager
{

  struct Plugin {

    Peripheral peripheral;

    bool connected;
    bool hidden;

    QMdiSubWindow* window;
    QPluginLoader* loader; // need to keep this for unloading

    QFileInfo file;

    QString id;
    QString description;
    QString version;

  };

public:

  /**
   * \brief Creates a PluginManager instance
   *
   * \note the use of \em peripheral and \em plugin are used interchangeably here
   * since plugins can only house peripherals at this point.
   *
   * \param io a pointer the io adpapter interface
   * \param mdiArea the mdiArea to house peripheral widgets
   */
  PluginManager( AVRIOAdapter* io, QMdiArea* mdiArea ) :
    io( io ), mdiArea( mdiArea ), plugins( new QMap<QString, Plugin*>() ) {}
  ~PluginManager() {}

public slots:

  /**
   * \brief show a plugin in the MdiArea specified in the constructor
   *
   * \param id the unique identifier for the peripheral
   */
  void show( const QString& id );

  /**
   * \brief hide a plugin from the MdiArea
   *
   * \param id the unique identifier for the peripheral
   */
  void hide( const QString& id );

  /**
   * \brief connects the logic component of a plugin to the logic signals
   * emitted by the avr cpu, this method will also make sure the affinity
   * of the logic component of the plugin is moved to the avr cpu thread.
   *
   * \see AbstractPeripheralLogic::connect( avr_t* )
   * \see AbstractPeripheralLogic::connect( AbstractPinFactory* )
   *
   * \param id the unique identifier for the peripheral
   */
  void connect( const QString& id );

  /**
   * \brief disconnects the logic component of a plugin from the logic
   * signals emitted by the avr cpu.
   *
   * \see AbstractPeripheralLogic::disconnect()
   *
   * \param id the unique identifier for the peripheral
   */
  void disconnect( const QString& id );

  /**
   * \brief free's any data structures and unloads the shared library
   * from the runtime environment.
   *
   * \param id the unique identifier for the peripheral
   */
  void unload( const QString& id );

  /**
   * \brief attempts to load a plugin
   *
   * \param pluginDirectory the directory containing the plugin
   * \param filename the filename of the plugin relative to the plugin directory
   */
  void load( const QDir& pluginDirectory, const QString& filename );

  /**
   * \brief lists the names of the plugins available, the name of the plugin
   * also serves as its unique identifier or \em id.
   *
   * \code{.cpp}
   *
   *  QList<QString> list = pluginmgr->listPlugins();
   *
   *  for ( int i = 0; i < list.count(); i++ ){
   *
   *    pluginmgr->load( list[i] );
   *
   *  }
   *
   * \endcode
   *
   * \return the list of names of all the available plugins
   */
  QList<QString> listPlugins( void );

private:

  AVRIOAdapter* io;
  QMdiArea* mdiArea;

  QMap<QString, Plugin*>* plugins;

};

#endif // PLUGINMANAGER_H
