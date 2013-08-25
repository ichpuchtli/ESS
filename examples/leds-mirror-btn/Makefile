##############################################################################
## Makefile for generating avr-cxx binaries compatible with simavr.
##############################################################################

PROJECT = main
TARGET = $(PROJECT).axf
SOURCES = $(PROJECT).c

CC = avr-gcc

## Supported AVR cores:
#	atmega88 atmega88p atmega88pa 
#	atmega328 atmega328p 
#	attiny44 
#	attiny25 
#	attiny24 
#	atmega1280 
#	attiny85 
#	atmega324 atmega324p atmega324pa 
#	attiny84 
#	atmega168 atmega168p atmega168pa 
#	atmega64 atmega64L 
#	atmega644 atmega644p 
#	atmega128 atmega128L 
#	at90usb162 
#	atmega164 atmega164p atmega164pa 
#	atmega8 atmega8l 
#	attiny45 
#	atmega1281 
#	attiny13 attiny13a 
#	attiny2313 attiny2313v 
#	atmega16m1 
#	atmega48 atmega48p atmega48pa 

## Target AVR Core
MCU = atmega64
F_CPU = 8000000UL

## Directory containing avr_mcu_section.h - AVR_MCU(), AVR_MCU_VCD_SYMBOL(), etc.
INCLUDES += -I../../../simavr/sim/avr

COMMON = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -g -std=gnu99 -Wall -Os 

CFLAGS += $(COMMON) 								\
	-gdwarf-2 -D__DELAY_BACKWARD_COMPATIBLE__  				\
	-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums 	\
	-fno-inline-small-functions -ffunction-sections -fdata-sections 	\
	-Wl,--relax,--gc-sections						\
	-Wl,--undefined=_mmcu,--section-start=.mmcu=0x910000

## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

all: $(TARGET) $(PROJECT).hex

$(TARGET): $(SOURCES) Makefile
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) -o $(TARGET)

$(PROJECT).hex: $(TARGET) size
	@avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

cpp:
	$(CC) -E -g $(CFLAGS) $(INCLUDES) -o main.cpp $(SOURCES)

## Clean target
.PHONY: clean
clean:
	rm -rf $(PROJECT).axf dep $(PROJECT).hex $(PROJECT).eep $(PROJECT).lss $(PROJECT).map $(PROJECT).cpp

flash: all
	sudo avrdude -e -y -c avrispmkii -p m64 -P usb -U flash:w:main.hex
