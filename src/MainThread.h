#ifndef __MAINTHREAD__
#define __MAINTHREAD__

#include <QThread>
#include <QString>

#include "sim_avr.h"
#include "sim_elf.h"

class MainThread : public QThread {

  public:
    MainThread();

    void run(void);
};

#endif
