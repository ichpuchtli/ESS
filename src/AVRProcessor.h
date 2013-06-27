#ifndef __AVRTHREAD__
#define __AVRTHREAD__

#include <QtCore/QThread>
#include <QtCore/QString>

#include "sim_avr.h"
#include "sim_elf.h"


class AVRProcessor : public QObject {

  Q_OBJECT

  public:
    AVRProcessor();
    ~AVRProcessor();

  public slots:

    void load(QString filename, QString mmcu, unsigned int frequency);

    void run(void);

  signals:

    void RESET();

    void loaded(avr_t* avr);

    void avrStateChange(int); // AVR Core state change // sleeping, running, stopped, finished

    void finished();

  private:
    avr_t* avr;
    elf_firmware_t firmware;

    QString filename;
    QString mmcu;

    unsigned int frequency;

    bool unlimited;

    void runUnlimited(void);
    void runRegulated(void);

    inline void loop_delay(unsigned int count);
};

#endif
