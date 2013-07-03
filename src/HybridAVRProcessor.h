#ifndef HYBRIDAVRPROCESSOR_H
#define HYBRIDAVRPROCESSOR_H

#include "AVRProcessor.h"

#include <QtCore/QTimer>

class HybridAVRProcessor : public AVRProcessor {

  Q_INTERFACES(AVRProcessor)

  public slots:

    void run(void);

  private:
    QTimer* timer;
    void update(void);
};

#endif
