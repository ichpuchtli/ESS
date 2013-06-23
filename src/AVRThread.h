#ifndef __AVRTHREAD__
#define __AVRTHREAD__

#include <QThread>
#include <QString>

#include "sim_avr.h"
#include "sim_elf.h"

class AVRThread : public QThread {

  Q_OBJECT

  public:
    AVRThread();

    void load(QString filename, QString mmcu, unsigned int frequency);

  protected:
    void run(void);

  public slots:

    void restart(void);

  signals:

    void RESET();

    void loaded(avr_t* avr);

    void avrStateChange(int); // AVR Core state change // sleeping, running, stopped, finished

  private:
    avr_t* avr;
    elf_firmware_t firmware;

    QString filename;
    QString mmcu;

    unsigned int frequency;

    bool unlimited;

    void runUnlimited(void);
    void runRegulated(void);

    void loop_delay(unsigned int count);
};

#endif
