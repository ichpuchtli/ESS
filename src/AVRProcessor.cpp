#include "AVRProcessor.h"

#include <QtCore/QDebug>

AVRProcessor::AVRProcessor(){

  this->avr = NULL;

}

AVRProcessor::~AVRProcessor(){

  if(this->avr){

    free(this->avr);
  }

}

/**
 * @brief load an avr firmware binary by filename, desired mmcu and frequency
 *
 * @param filename the filename of the firmware binary to load
 * @param mmcu the target avr core (atmega64,atmega128,...)
 * @param frequency the desired frequency of the simulation generally 8MHz
 */
void AVRProcessor::load(const QString& filename, const QString& mmcu, unsigned frequency) {

  this->filename = QString(filename);

  this->mmcu = QString(mmcu);

  this->frequency = frequency;

  elf_read_firmware(filename.toLatin1(), &this->firmware);

  this->firmware.frequency = frequency;

  memcpy(this->firmware.mmcu, mmcu.toLatin1(), mmcu.size() );

  qDebug() << "AVRProcessor:" << this->filename.toLatin1() << " freq "
    << frequency << " mmcu " << mmcu.toLatin1();

  this->avr = avr_make_mcu_by_name(mmcu.toLatin1());

  if(!this->avr){
      qDebug() << "AVRProcessor: possible memory allocation error\n";
      return;
  }

  avr_init(this->avr);

  avr_load_firmware(this->avr, &this->firmware);

  fflush(stdout);

  emit this->loaded(this->avr);
}
