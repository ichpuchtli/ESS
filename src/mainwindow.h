/**
 * \file mainwindow.h
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtCore/QThread>
#include "ui_mainwindow.h"

#include "AVRProcessor.h"

/**
 * \brief the main class controlling simulations and the main window
 */
class MainWindow : public QMainWindow {

  Q_OBJECT

  public:
    MainWindow( QWidget* parent = 0 );
    ~MainWindow();


  public slots:

    /**
     * \brief a simple slot to load firmware using a file dialog
     */
    void loadFirmware(void);

  /**
   * \brief stops execution before reloading firmware and restarting execution
   */
    void reloadFirmware(void);

    /**
     * \brief starts execution of the simulation engine
     */
    void startSimulation(void);

    /**
     * \brief stops execution of the simulation engine
     */
    void stopSimulation(void);

  private:

    void initSettings(void);
    void initComponents(void);

    void connectActions(void);

    Ui::MainWindow *ui;

    QString filename;

    AVRProcessor* cpu;
    QThread* cpuThread;
};

#endif // MAINWINDOW_H
