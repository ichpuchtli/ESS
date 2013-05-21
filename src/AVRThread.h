#ifndef __AVRTHREAD__
#define __AVRTHREAD__

#include <QThread>
#include <QString>

#include "sim_avr.h"
#include "sim_elf.h"

class AVRThread : public QThread {

  public:
    AVRThread(QString filename, QString mmcu, unsigned int frequency);
    AVRThread(QString filename);
    AVRThread(avr_t* avr);
    AVRThread();

    avr_t* getAVR(void);

    void RESET(void);

    void run(void);

    bool verbose;
    
  private:
    avr_t* avr;
    int status;

    static void loop_delay(long loop_count);

};

#endif
