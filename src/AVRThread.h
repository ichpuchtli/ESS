#ifndef __AVRTHREAD__
#define __AVRTHREAD__

#include <QThread>
#include <QString>

#include "sim_avr.h"
#include "sim_elf.h"

typedef char port_t;
typedef char pin_t;

const char NUM_AVR_PORTS = 7;
const char AVR_PORT[NUM_AVR_PORTS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};

class AVRThread : public QThread {

  //Q_OBJECT

  public:
    AVRThread(QString filename, QString mmcu, unsigned int frequency);
    AVRThread(QString filename);
    AVRThread(avr_t* avr);
    AVRThread(const AVRThread& rhs);
    AVRThread(); // Prevent this case once testing is finished with a throw?

    void run(void);

  public slots:

    void RESET(void);
    void setFrequency(int);

    void andPort(port_t, pin_t);
    void orPort(port_t, pin_t);
    void xorPort(port_t, pin_t);

    void mutePort(port_t, pin_t);
    void unMutePort(port_t, pin_t);

    // Handles IRQ's and emits corrosponding Qt signal
    void irq_handler(struct avr_irq_t* irq, uint32_t value, void* param);

  signals:

    // Signalled when any port not muted changes level
    //void pinChange(port_t, pin_t);

    // Signalled when any port not muted changes direction i.e. Input/Ouput
    //void ddChange(port_t, pin_t);

  private:
    avr_t* avr;
    int status;
    int frequency;
    bool verbose;

    void loop_delay(long loop_count);

    // maps irq to irq_handler();
    void connect_irqs(void);



};

#endif
