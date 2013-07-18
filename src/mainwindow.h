#include <QtWidgets/QMainWindow>
#include <QtCore/QThread>
#include "ui_mainwindow.h"

#include "AVRProcessor.h"

class MainWindow : public QMainWindow {

  Q_OBJECT

  public:
    MainWindow( QWidget* parent = 0 );
    ~MainWindow();

  public slots:
    void loadFirmware(void);
    void reloadFirmware(void);

    void startSimulation(void);
    void stopSimulation(void);

  private:

    void initSettings(void);
    void initComponents(void);

    void connectActions(Ui::MainWindow* ui);

    Ui::MainWindow *ui;

    QString filename;

    AVRProcessor* cpu;
    QThread* cpuThread;
};
