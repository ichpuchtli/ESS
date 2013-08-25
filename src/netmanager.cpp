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

NetManager::NetManager( QWidget* parent ) : QTreeWidget( parent ),
  itemMap( new QMap<QString, QTreeWidgetItem*>() )
{

  connect( this, &QTreeWidget::itemChanged, this, &NetManager::itemChangeEvent );

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

void NetManager::itemChangeEvent( QTreeWidgetItem* item, int index )
{

  ( void ) index;

  if ( item->parent() ) {

    QString net = item->text( 0 );
    QString pin = item->text( 1 );

    QString pluginId = item->parent()->text( 0 );

    if ( pin.size() == 3 ) { //TODO proper regex test here
      emit this->netChanged( pluginId, net, pin );
    }


  } else {

    QString pid = item->text( 0 );

    bool checked = ( item->checkState( 0 ) == Qt::Checked );

    checked ? this->enablePlugin( pid ) : this->disablePlugin( pid );

    item->setExpanded( checked );

    checked ? this->pluginEnabled( pid ) : this->pluginDisabled( pid );

  }

}
