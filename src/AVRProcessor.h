#ifndef AVRPROCESSOR_H
#define AVRPROCESSOR_H

#include <QtCore/QObject>
#include <QtCore/QString>

#include "sim_avr.h"
#include "sim_elf.h"

class AVRProcessor : public QObject {

  Q_OBJECT

public:

  AVRProcessor();
  virtual ~AVRProcessor();

  // Signals
  signals:

  void RESET();

  void finished();

  void loaded(avr_t* avr);

  void avrStateChange(int status);

  // Slots
  public slots:

  virtual void run() = 0; // Pure Virtual, Base class must implement run

  void load(const QString& filename, const QString& mmcu, unsigned frequency);

protected:
  avr_t* avr;
  elf_firmware_t firmware;

  QString filename;
  QString mmcu;
  unsigned frequency;

};

Q_DECLARE_INTERFACE(AVRProcessor, "ESS.AVRProcessor")

#endif // AVRPROCESSOR_H
