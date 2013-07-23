/********************************************************************************
** Form generated from reading UI file 'mainwindowF15754.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOWF15754_H
#define MAINWINDOWF15754_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_Session;
    QAction *actionSave_Session;
    QAction *actionClose;
    QAction *actionESS_Help;
    QAction *actionAbout_ESS;
    QAction *actionAbout_Qt;
    QAction *actionLoad_Firmware;
    QAction *actionPause;
    QAction *actionStop;
    QAction *actionReload_Firmware;
    QAction *actionStart;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QMdiArea *mdiArea;
    QTextEdit *logViewer;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuPlugins;
    QMenu *menuHelp;
    QMenu *menuAVR;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(640, 480);
        actionOpen_Session = new QAction(MainWindow);
        actionOpen_Session->setObjectName(QStringLiteral("actionOpen_Session"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/media/icons/document-open-folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_Session->setIcon(icon);
        actionSave_Session = new QAction(MainWindow);
        actionSave_Session->setObjectName(QStringLiteral("actionSave_Session"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/media/icons/document-save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_Session->setIcon(icon1);
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/media/icons/application-exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClose->setIcon(icon2);
        actionESS_Help = new QAction(MainWindow);
        actionESS_Help->setObjectName(QStringLiteral("actionESS_Help"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/media/icons/help-contents.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionESS_Help->setIcon(icon3);
        actionAbout_ESS = new QAction(MainWindow);
        actionAbout_ESS->setObjectName(QStringLiteral("actionAbout_ESS"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/media/icons/help-about.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout_ESS->setIcon(icon4);
        actionAbout_Qt = new QAction(MainWindow);
        actionAbout_Qt->setObjectName(QStringLiteral("actionAbout_Qt"));
        actionAbout_Qt->setIcon(icon4);
        actionAbout_Qt->setMenuRole(QAction::AboutQtRole);
        actionLoad_Firmware = new QAction(MainWindow);
        actionLoad_Firmware->setObjectName(QStringLiteral("actionLoad_Firmware"));
        actionLoad_Firmware->setIcon(icon);
        actionPause = new QAction(MainWindow);
        actionPause->setObjectName(QStringLiteral("actionPause"));
        actionPause->setCheckable(false);
        actionPause->setChecked(false);
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/media/icons/media-playback-pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPause->setIcon(icon5);
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QStringLiteral("actionStop"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/media/icons/media-playback-stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStop->setIcon(icon6);
        actionReload_Firmware = new QAction(MainWindow);
        actionReload_Firmware->setObjectName(QStringLiteral("actionReload_Firmware"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/media/icons/view-refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionReload_Firmware->setIcon(icon7);
        actionStart = new QAction(MainWindow);
        actionStart->setObjectName(QStringLiteral("actionStart"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/media/icons/media-playback-start.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStart->setIcon(icon8);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Vertical);
        mdiArea = new QMdiArea(splitter);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));
        splitter->addWidget(mdiArea);
        logViewer = new QTextEdit(splitter);
        logViewer->setObjectName(QStringLiteral("logViewer"));
        logViewer->setMinimumSize(QSize(0, 30));
        logViewer->setUndoRedoEnabled(false);
        logViewer->setReadOnly(false);
        logViewer->setTextInteractionFlags(Qt::TextEditorInteraction);
        splitter->addWidget(logViewer);

        horizontalLayout->addWidget(splitter);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 640, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuPlugins = new QMenu(menubar);
        menuPlugins->setObjectName(QStringLiteral("menuPlugins"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuAVR = new QMenu(menubar);
        menuAVR->setObjectName(QStringLiteral("menuAVR"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuAVR->menuAction());
        menubar->addAction(menuPlugins->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen_Session);
        menuFile->addAction(actionSave_Session);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        menuHelp->addAction(actionESS_Help);
        menuHelp->addSeparator();
        menuHelp->addAction(actionAbout_ESS);
        menuHelp->addAction(actionAbout_Qt);
        menuAVR->addAction(actionLoad_Firmware);
        menuAVR->addAction(actionReload_Firmware);
        menuAVR->addSeparator();
        menuAVR->addAction(actionStart);
        menuAVR->addAction(actionPause);
        menuAVR->addAction(actionStop);
        menuAVR->addSeparator();
        toolBar->addAction(actionLoad_Firmware);
        toolBar->addAction(actionReload_Firmware);
        toolBar->addSeparator();
        toolBar->addAction(actionStart);
        toolBar->addAction(actionPause);
        toolBar->addAction(actionStop);
        toolBar->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOpen_Session->setText(QApplication::translate("MainWindow", "Open Session", 0));
        actionSave_Session->setText(QApplication::translate("MainWindow", "Save Session", 0));
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0));
        actionESS_Help->setText(QApplication::translate("MainWindow", "ESS Help", 0));
        actionAbout_ESS->setText(QApplication::translate("MainWindow", "About ESS", 0));
        actionAbout_Qt->setText(QApplication::translate("MainWindow", "About Qt", 0));
#ifndef QT_NO_STATUSTIP
        actionAbout_Qt->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        actionLoad_Firmware->setText(QApplication::translate("MainWindow", "Load Firmware", 0));
        actionPause->setText(QApplication::translate("MainWindow", "Pause", 0));
        actionStop->setText(QApplication::translate("MainWindow", "Stop", 0));
        actionReload_Firmware->setText(QApplication::translate("MainWindow", "Reload Firmware", 0));
        actionReload_Firmware->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", 0));
        actionStart->setText(QApplication::translate("MainWindow", "Start", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuPlugins->setTitle(QApplication::translate("MainWindow", "Peripherals", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
        menuAVR->setTitle(QApplication::translate("MainWindow", "AVR", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOWF15754_H
