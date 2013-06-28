#ifndef REGULATEDAVRPROCESSOR_H
#define REGULATEDAVRPROCESSOR_H

#include "AVRProcessor.h"

class RegulatedAVRProcessor : public AVRProcessor {

  Q_INTERFACES(AVRProcessor)

  public slots:

    void run(void);

  private:

    inline void loop_delay(unsigned int count);
};

#endif
