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

PluginManager::PluginManager(QDir pluginDir, QThread* affinity, QMdiArea* mdiArea, avr_t* avr, PinFactory* pinFactory):
  plugins(new QMap<QString, Plugin*>()),
  pluginDir(pluginDir),
  affinity(affinity),
  mdiArea(mdiArea),
  pinFactory(pinFactory),
  avr(avr)
{

  QStringList libs;

  libs = pluginDir.entryList(QDir::Files | QDir::NoDotAndDotDot);

  qDebug() << "PluginManager: Found (" << libs.count() << ") Plugins" << libs;

  foreach(const QString& filename, libs) {
    this->load(filename);
  }

}

void PluginManager::unload( const QString& id ){}

void PluginManager::load(const QString& filename){

  QDir path(this->pluginDir.dirName() + "/" + filename);

  QPluginLoader* loader = new QPluginLoader(path.absolutePath());

  if(loader->metaData().isEmpty()){
    qDebug() << "PluginManager: could not find meta data on plugin:" << filename;
    delete loader;
    return;
  }

  QObject* library = loader->instance();

  if(!library){

    qDebug() << "PluginManager: error loading " << filename << "["
             << loader->errorString() << "]";
  }

  Plugin* plugin = new Plugin;

  plugin->hidden = true;
  plugin->loaded = true;
  plugin->connected = false;
  plugin->peripheral.logic = NULL;
  plugin->peripheral.widget = NULL;

  AbstractPeripheralFactory* factory;
  factory = qobject_cast<AbstractPeripheralFactory*>(library);

  if(!factory) {

    qDebug() << "PluginManager: error casting plugin to "
                "AbstractPeripheralFactory check implementation";

    plugin->loaded = false;

    qDebug() << "PluginManager: could not load" << filename;

  }else{

    plugin->peripheral = factory->getPeripheral();
    plugin->description = factory->getDescription();
    plugin->version = factory->getVersion();

    delete factory; // Done with factory

    qDebug() << "PluginManager: sucessfully loaded" << filename;
  }

  QString id = loader->metaData().value("IID").toString();

  plugin->id = id;
  plugin->path = path;
  plugin->loader = loader;

  this->plugins->insert(id, plugin);

}

void PluginManager::show(const QString& id){

  Plugin* plugin = this->plugins->value(id);

  if(plugin->loaded && plugin->hidden){

    this->mdiArea->addSubWindow(plugin->peripheral.widget);

    plugin->hidden = false;

  }

}

void PluginManager::hide(const QString& id){

  Plugin* plugin = this->plugins->value(id);

  if(plugin->loaded && !plugin->hidden){
    this->mdiArea->removeSubWindow(plugin->peripheral.widget);
    plugin->hidden = true;
  }

}

void PluginManager::connect(const QString& id){

  Plugin* plugin = this->plugins->value(id);

  //TODO connect RESET and error signals
  //connect(logic,RESET,pinRESET,fallingEdge);
  if(plugin->loaded && !plugin->connected) {

    plugin->peripheral.logic->moveToThread(this->affinity);

    plugin->peripheral.logic->connect(this->pinFactory);
    plugin->peripheral.logic->connect(this->avr);

    plugin->connected = true;
  }


}

void PluginManager::disconnect(const QString &id){

  Plugin* plugin = this->plugins->value(id);

  if(plugin->loaded && plugin->connected) {
    plugin->peripheral.logic->disconnect();
    plugin->connected = false;
  }

}

QList<QString> PluginManager::listPlugins(void){
  return this->plugins->keys();
}
