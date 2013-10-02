/**
 * \file netmanager.cpp
 * \brief A class for managing net list configurations
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

#include "netmanager.h"
#include <QtGui/QResizeEvent>
#include <QtCore/QSettings>
#include <QtCore/QStringList>

NetManager::NetManager( QWidget* parent ) : QTreeWidget( parent ),
  itemMap( new QMap<QString, QTreeWidgetItem*>() )
{

  connect( this, &QTreeWidget::itemChanged, this, &NetManager::itemChangeEvent );
  connect( this, &QTreeWidget::itemDoubleClicked, this,
           &NetManager::itemEditEvent );

  this->setEditTriggers( QAbstractItemView::NoEditTriggers );

}

NetManager::~NetManager()
{

  for ( int i = 0; i < this->topLevelItemCount(); i++ ) {

    QTreeWidgetItem* item = this->topLevelItem( 0 );

    for ( int j = 0; j < item->childCount(); j++ ) {
      delete item->child( j );
    }

    delete item;

  }

}

void NetManager::keyPressEvent( QKeyEvent *event )
{

  if ( event->key() == Qt::Key_Return ) {

    event->accept();

    if ( currentItem() ) {

      QTreeWidgetItem* nextItem = itemBelow( currentItem() );

      if ( nextItem && ( nextItem->childCount() == 0 ) ) {
        setCurrentItem( nextItem, 1 );
        editItem( nextItem, 1 );
      }

    }

  } else {

    QTreeWidget::keyPressEvent( event );

  }

}

void NetManager::addPlugin( const QString &id, const QStringList &nets )
{

  QTreeWidgetItem* pluginItem = new QTreeWidgetItem( ( QTreeWidget* ) 0,
      QStringList() << id  << "" );

  pluginItem->setFlags( pluginItem->flags() | Qt::ItemIsUserCheckable );
  pluginItem->setCheckState( 0, Qt::Unchecked );

  for ( int i = 0; i < nets.size(); i++ ) {
    QTreeWidgetItem* net = new QTreeWidgetItem( ( QTreeWidget* )0,
        QStringList() << nets[i] << "NC" );
    net->setFlags( Qt::ItemIsSelectable );
    pluginItem->addChild( net );
  }

  this->addTopLevelItem( pluginItem );

  pluginItem->setFirstColumnSpanned( true );

  this->itemMap->insert( id, pluginItem );

}

void NetManager::enablePlugin( const QString &id )
{

  QTreeWidgetItem* item = this->itemMap->value( id );

  for ( int i = 0; i < item->childCount(); i++ ) {
    item->child( i )->setFlags( Qt::ItemIsEditable | Qt::ItemIsSelectable |
                                Qt::ItemIsEnabled );
  }
}

void NetManager::disablePlugin( const QString &id )
{

  QTreeWidgetItem* item = this->itemMap->value( id );

  for ( int i = 0; i < item->childCount(); i++ ) {
    item->child( i )->setFlags( Qt::ItemIsSelectable );
  }

}

void NetManager::itemEditEvent( QTreeWidgetItem* item, int column )
{

  if ( column == 1 ) {
    editItem( item, column );
  }

}

void NetManager::itemChangeEvent( QTreeWidgetItem* item, int column )
{

  QSettings settings;

  if ( item->parent() ) {

    // Ignore changes to the Net Column
    if ( column == 0 ) {
      return;
    }

    QString net = item->text( 0 );
    QString pin = item->text( 1 );

    QString pluginId = item->parent()->text( 0 );

    if ( pin.size() == 3 ) { //TODO proper regex test here
      emit this->netChanged( pluginId, net, pin );
    }

    settings.beginGroup( pluginId );
    settings.setValue( net, pin );
    settings.endGroup();

  } else {

    QString pid = item->text( 0 );

    bool checked = ( item->checkState( 0 ) == Qt::Checked );

    checked ? this->enablePlugin( pid ) : this->disablePlugin( pid );

    item->setExpanded( checked );

    checked ? this->pluginEnabled( pid ) : this->pluginDisabled( pid );

    settings.beginGroup( "plugins" );
    settings.setValue( pid, checked );
    settings.endGroup();

  }

}

QTreeWidgetItem* NetManager::findChild( QTreeWidgetItem* parent, QString net )
{

  QTreeWidgetItem* childItem = NULL;

  for ( int i = 0; i < parent->childCount(); i++ ) {

    QTreeWidgetItem* tmp = parent->child( i );

    if ( tmp && tmp->text( 0 ) == net ) {
      childItem = tmp;
      break;
    }

  }

  return childItem;

}

void NetManager::loadSettings()
{

  QSettings settings;

  settings.beginGroup( "plugins" );

  QList<QString> holder = settings.allKeys();

  settings.endGroup();

  foreach( const QString id, holder ) {

    QTreeWidgetItem* item = this->itemMap->value( id );

    settings.beginGroup( "plugins" );

    if ( settings.value( id, false ).toBool() ) {

      settings.endGroup();

      item->setCheckState( 0, Qt::Checked );

      this->enablePlugin( id );
      this->pluginEnabled( id );

      settings.beginGroup( id );

      foreach( const QString net, settings.allKeys() ) {

        QString pin = settings.value( net ).toString();

        QTreeWidgetItem* child = findChild( item, net );

        if ( child ) {
          child->setText( 1, pin );
        }

        emit this->netChanged( id, net, pin );

      }

    }

    settings.endGroup();

  }

}
