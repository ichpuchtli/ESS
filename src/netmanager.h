/**
 * \file netmanager.h
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
#ifndef NETMANAGER_H
#define NETMANAGER_H

#include <QtWidgets/QTreeWidget>
#include <QStringList>

/**
 * \brief A class for managing net list configurations
 */
class NetManager : public QTreeWidget
{

  Q_OBJECT

public:

  NetManager( QWidget* parent = 0 );
  ~NetManager();

public slots:

  /**
   * \brief adds a plugin along with its available nets to the table
   *
   * \param id the name/id of the plugin
   * \param nets a list of nets available to connect to
   */
  void addPlugin( const QString& id, const QStringList& nets );

  /**
   * @brief load configuration
   */
  void loadSettings( void );

signals:

  /**
   * \brief this signal is emitted when the \em pin associated with the \em net
   * is changed
   *
   * \param id the name/id of the plugin
   * \param net the name of the net
   * \param pin the new pin to be connected to the net
   */
  void netChanged( QString id, QString net, QString pin );

  /**
   * \brief this signal is emitted when the plugin is enabled from the table
   *
   * \param id the name/id of the plugin
   */
  void pluginEnabled( QString id );

  /**
   * \brief this signal is emitted when the plugin is disabled from the table
   *
   * \param id the name/id of the plugin
   */
  void pluginDisabled( QString id );

protected:
  virtual void keyPressEvent( QKeyEvent *event );

private:

  void enablePlugin( const QString& id );
  void disablePlugin( const QString& id );

  void itemChangeEvent( QTreeWidgetItem* item , int column );
  void itemEditEvent( QTreeWidgetItem* item , int column );

  QTreeWidgetItem* findChild( QTreeWidgetItem* parent, QString net );

  QMap<QString, QTreeWidgetItem*>* itemMap;

};

#endif // NETMANAGER_H
