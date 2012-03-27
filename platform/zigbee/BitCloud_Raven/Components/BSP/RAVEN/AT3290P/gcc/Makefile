###############################################################################
# Makefile for the project avrraven_3290p
###############################################################################

## General Flags
PROJECT = avrraven_3290p
MCU = atmega3290p
TARGET = avrraven_3290p.elf
CC = avr-gcc
TOP_DIR = ..

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99 -DAVR  -DAVRRAVEN_3290P -D__ATmega3290P__ -DAVRRAVEN_3290P_APP_REV_MAJ=1 -DAVRRAVEN_3290P_APP_REV_MIN=1 -DF_CPU=4000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=avrraven_3290p.map
#LDFLAGS += -Wl,-section-start=FW_REV_ADR_M3290P_APP=0xdffe


## Intel Hex file production flags
#HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
INCLUDES += -I$(TOP_DIR)/configure/arch
INCLUDES += -I$(TOP_DIR)/configure/arch/avr/dev
INCLUDES += -I$(TOP_DIR)/configure/application/avrraven
INCLUDES += -I$(TOP_DIR)/configure/application/avrraven/3290p
INCLUDES += -I$(TOP_DIR)/configure/application/avrraven/3290p/drivers 
INCLUDES += -I$(TOP_DIR)/configure/application/avrraven/3290p/board_peripherals
INCLUDES += -I$(TOP_DIR)/include/application/avrraven
INCLUDES += -I$(TOP_DIR)/board
INCLUDES += -I$(TOP_DIR)/include/application/avrraven/3290p
INCLUDES += -I$(TOP_DIR)/include
INCLUDES += -I$(TOP_DIR)/include/vrt
INCLUDES += -I$(TOP_DIR)/include/arch/avr
INCLUDES += -I$(TOP_DIR)/include/application/avrraven/3290p/drivers 
INCLUDES += -I$(TOP_DIR)/include/application/avrraven/3290p/menu
INCLUDES += -I$(TOP_DIR)/include/application/avrraven/3290p/board_peripherals
INCLUDES += -I$(TOP_DIR)/configure/vrt
INCLUDES += -I$(TOP_DIR)/../include

## Objects that must be built in order to link
OBJECTS = adc.o asy_tmr.o avrraven_3290p.o battery.o bcd.o cmd_if_3290p.o extern_sipc_cmd.o int_evt.o lcd.o led.o sipc.o spi.o tick.o vrt_kernel.o vrt_mem.o temp.o

## Objects explicitly added by the user
LINKONLYOBJECTS = 

VPATH = \
  $(TOP_DIR)/application/avrraven/3290p \
  $(TOP_DIR)/application/avrraven/3290p/board_peripherals \
  $(TOP_DIR)/application/avrraven/3290p/drivers \
  $(TOP_DIR)/arch/avr/dev \
  $(TOP_DIR)/vrt \

## Build
all: $(TARGET) avrraven_3290p.hex avrraven_3290p.eep avrraven_3290p.lss size

## Compile
%.o: %.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
#.PHONY: clean
clean:
	-rm -rf $(OBJECTS) avrraven_3290p.elf dep/* avrraven_3290p.hex avrraven_3290p.eep avrraven_3290p.lss avrraven_3290p.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

