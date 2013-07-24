/**
 * \file PluginManager.cpp
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

#include "PluginManager.h"

#include <QtCore/QDebug>

void PluginManager::unload( const QString& id ){

  Plugin* plugin = this->plugins->value(id);

  this->plugins->remove(id);

  this->hide(id);
  this->disconnect(id);

  this->mdiArea->removeSubWindow(plugin->window);

  //TODO dangerous if signals are still connected etc.
  delete plugin->peripheral.widget;
  delete plugin->peripheral.logic;

  delete plugin->window;

  plugin->loader->unload();

  delete plugin->loader;

  delete plugin;

}

void PluginManager::load(const QDir& pluginDirectory, const QString& filename ){

  QFileInfo file = QFileInfo(pluginDirectory, filename);

  QPluginLoader* loader = new QPluginLoader(file.absoluteFilePath());

  if(loader->metaData().isEmpty()){

    qDebug() << "PluginManager: could not find meta data on plugin:" << filename;

    delete loader;

    return;
  }

  QObject* library = loader->instance();

  if(!library){

    qDebug() << "PluginManager:" << loader->errorString();

    qDebug() << "PluginManager: could not load" << filename;

    delete loader;

    return;
  }

  AbstractPeripheralFactory* factory;
  factory = qobject_cast<AbstractPeripheralFactory*>(library);

  if(!factory) {

    qDebug() << "PluginManager: error casting plugin to "
                "AbstractPeripheralFactory check implementation";

    qDebug() << "PluginManager: could not load" << filename;

    delete library;
    delete loader;

    return;
  }

  Plugin* plugin = new Plugin;

  plugin->peripheral = factory->getPeripheral();
  plugin->description = factory->getDescription();
  plugin->version = factory->getVersion();

  delete factory; // Done with factory

  plugin->window = new QMdiSubWindow(this->mdiArea);
  plugin->window->setWidget(plugin->peripheral.widget);
  plugin->window->hide();
  this->mdiArea->addSubWindow(plugin->window);

  plugin->hidden = true;
  plugin->connected = false;

  QString id = loader->metaData().value("IID").toString();

  plugin->id = id;
  plugin->file = file;
  plugin->loader = loader;

  this->plugins->insert(id, plugin);

  qDebug() << "PluginManager: sucessfully loaded" << filename;

}

void PluginManager::show(const QString& id){

  Plugin* plugin = this->plugins->value(id);

  if(plugin->hidden){
    plugin->window->show();
    plugin->hidden = false;
  }

}

void PluginManager::hide(const QString& id){

  Plugin* plugin = this->plugins->value(id);

  if(!plugin->hidden){
    //TODO create MdiSubWindow object so windows can be hidden/shown
    plugin->window->hide();
    plugin->hidden = true;
  }

}

void PluginManager::connect(const QString& id){

  Plugin* plugin = this->plugins->value(id);

  //TODO connect RESET and error signals
  //connect(logic,RESET,pinRESET,fallingEdge);
  if(!plugin->connected) {

    plugin->peripheral.logic->moveToThread(this->io->getThread());

    plugin->peripheral.logic->connect(this->io);

    plugin->connected = true;
  }


}

void PluginManager::disconnect(const QString &id){

  Plugin* plugin = this->plugins->value(id);

  if(plugin->connected) {
    plugin->peripheral.logic->disconnect();
    plugin->connected = false;
  }

}

QList<QString> PluginManager::listPlugins(void){
  return this->plugins->keys();
}
