#ifndef RRAVRPROCESSOR_H
#define RRAVRPROCESSOR_H

#include "AVRProcessor.h"

class RRAVRProcessor : public AVRProcessor {

  Q_INTERFACES(AVRProcessor)

  public slots:

    void run(void);
};

#endif
