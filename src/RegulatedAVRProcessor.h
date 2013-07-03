#ifndef REGULATEDAVRPROCESSOR_H
#define REGULATEDAVRPROCESSOR_H

#include "AVRProcessor.h"

class RegulatedAVRProcessor : public AVRProcessor {

  Q_INTERFACES(AVRProcessor)

  public slots:

    void run(void);

  /**
   * @brief simple loop delay (spin delay, spin counter, etc)
   *
   * @param count the number of "nop" to execute, to create a significant delay
   */
  static inline void loop_delay(unsigned int count){

    while(count--) asm("nop");

  }

};

#endif
