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

  /**
   * @brief returns true if the simavr core is still running and has not crashed nor
   * reached the end of program code
   *
   * @param status the enum returned by avr_run( avr_t* avr ) from simavr which executes a single
   * operation
   */
  inline bool avrRunnable( int status ){

    return ( status != cpu_Crashed ) && ( status != cpu_Done );

  }

protected:
  avr_t* avr;
  elf_firmware_t firmware;

  QString filename;
  QString mmcu;
  unsigned frequency;

};

Q_DECLARE_INTERFACE(AVRProcessor, "ESS.AVRProcessor")

#endif // AVRPROCESSOR_H
