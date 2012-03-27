#==============================================================================
#  The file builds the application.
#  \author
#    Atmel Corporation: http://www.atmel.com \n
#    Support email: avr@atmel.com
#
#  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
#  Licensed under Atmel's Limited License Agreement (BitCloudTM).
#==============================================================================

#==============================================================================
# Rules and options collecting
#==============================================================================
include Configuration

SDDS_LIB=sdds

# Schematic of STK600-Atmega128RFA1 is the same as schematic of RCB_ATMEGA128RFA1
ifeq ($(BOARD), BOARD_STK600_ATMEGA128RFA1)
  BOARD = BOARD_RCB
  BOARD_REV = RCB_ATMEGA128RFA1
  BSP_ENABLE_RS232_CONTROL = 0
endif # BOARD_STK600_ATMEGA128RFA1
# RS-232 control should be disabled on all platforms, except RCB
ifneq ($(BOARD), BOARD_RCB)
  BSP_ENABLE_RS232_CONTROL = 0
endif

# Extracting Configuration Server (CS_...) and Apllication (App_...) specific parameters
CS_PARAMS := $(filter CS_%, $(.VARIABLES))
APP_PARAMS := $(filter APP_%, $(.VARIABLES))
BSP_PARAMS := $(filter BSP_%, $(.VARIABLES))
# sDDS specific stuff
SDDS_PARAMS := $(filter sDDS_%, $(.VARIABLES))

# Detecting Makerules file name which shall be inherited from stack.
include $(COMPONENTS_PATH)/../lib/MakerulesSelector
#MAKERULES = $(realpath, $(COMPONENTS_PATH)/../lib/$(LIB_MAKERULES)) # use this line once bug is fixed
# workaround GNU make 3.81 bug on windows platform
realpath_ = $(join \
            $(filter %:,$(subst :,: ,$1)),\
            $(realpath $(filter-out %:,$(subst :,: ,$1)))) 
MAKERULES = $(call realpath_, $(COMPONENTS_PATH)/../lib/$(LIB_MAKERULES))

# Stack Makerules inheriting
include $(MAKERULES)
# Board specific options detecting
include $(BSP_PATH)/BoardConfig

#==============================================================================
# Stack and device type compatibility verification
#==============================================================================
# Sliders boards don't use APP_DEVICE_TYPE.
ifeq (, $(filter -D_SLIDERS_, $(BOARDCFLAGS)))
  ifneq ($(STACK_TYPE), ALL_DEVICES_TYPES)
    ifdef APP_DEVICE_TYPE
      ifneq (DEV_TYPE_$(STACK_TYPE), $(APP_DEVICE_TYPE))
        $(error ERROR: Unsupported application configuration: STACK_TYPE=$(STACK_TYPE), but APP_DEVICE_TYPE=$(APP_DEVICE_TYPE). Please, correct the Configuration)
      endif # equality check
    endif # APP_DEVICE_TYPE defined
  endif # ALL_DEVICES_TYPES
endif #SLIDERS

#==============================================================================
# Hardware parameters 
#==============================================================================
HW_PARAMS = $(HAL_FREQUENCY)
ifeq ($(BOARD), BOARD_RCB)
  HW_PARAMS += $(BOARD_REV)
endif

#==============================================================================
# Stack parameters being set to Config Server
#==============================================================================

# Test network dependent parameters being set to Config Server
ifeq ($(TEST_NETWORK), 1)
  CFLAGS += -DTEST_NETWORK
  CS_PARAMS += CS_NWK_ADDR
endif

#==============================================================================
# Generate FLAGS based on specified parameters
#==============================================================================
CFLAGS_CS  = $(foreach PARAM, $(CS_PARAMS), -D$(PARAM)=$(value $(PARAM)))
CFLAGS_APP = $(foreach PARAM, $(APP_PARAMS), -D$(PARAM)=$(value $(PARAM)))
CFLAGS_BSP = $(foreach PARAM, $(BSP_PARAMS), -D$(PARAM)=$(value $(PARAM)))
CFLAGS_HW = $(foreach PARAM, $(HW_PARAMS), -D$(PARAM))
# extension for sdds
CFLAGS_SDDS = $(foreach PARAM, $(SDDS_PARAMS), -D$(PARAM)=$(value $(PARAM)))

# CFLAGS extending with specified parameters.
CFLAGS += $(CFLAGS_CS) $(CFLAGS_APP) $(CFLAGS_BSP) $(CFLAGS_HW) $(CFLAGS_SDDS)

#==============================================================================
# Output debug port for ARM platforms only 
#==============================================================================
ifeq ($(HAL), AT91SAM7X256)
  ifeq ($(DEBUG), 1)
    CFLAGS += -D_DBG_
  endif
endif

#==============================================================================
# Compiler specific flags
#==============================================================================
ifeq ($(DEBUG), 1)
  ifeq ($(COMPILER_TYPE), GCC)
    CFLAGS_DBG += -g -Os
  endif
  ifeq ($(COMPILER_TYPE), IAR)
    CFLAGS_DBG += --debug
  endif
  # Compiler flags extending with "debug info" compiler flag.
  CFLAGS += $(CFLAGS_DBG)
endif

#==============================================================================
# Include paths flags
#==============================================================================
INCLUDEDIRS =                        \
	-I$(APP_PATH)/include            \
	-I$(AVRSTUB_PATH)/include		 \
	-I$(SE_PATH)/include             \
	-I$(APS_PATH)/include            \
	-I$(NWK_PATH)/include            \
	-I$(ZDO_PATH)/include            \
	-I$(MAC_PHY_PATH)/include        \
	-I$(HAL_PATH)/include            \
	-I$(HAL_HWD_COMMON_PATH)/include \
	-I$(HAL_PATH)/drivers/include    \
	-I$(BSP_PATH)/include            \
	-I$(CS_PATH)/include             \
	-I$(PDS_PATH)/include            \
	-I$(TC_PATH)/include             \
	-I$(SSP_PATH)/include            \
	-I$(OTAU_SERVER_PATH)/include    \
	-I$(SDDS_PATH)/include			\

#==============================================================================
# Libraries paths
#==============================================================================
ifeq ($(COMPILER_TYPE), GCC)
  LIBDIRS  = -L$(COMPONENTS_PATH)/../lib
  LIBDIRS += -L$(BSP_PATH)/lib
  LIBDIRS += -L$(CS_PATH)/lib
  LIBDIRS += -L$(PDS_PATH)/lib
  ifeq ($(APP_USE_OTAU), 1)
    LIBDIRS += -L$(OTAU_SERVER_PATH)/lib
  endif
  ifeq ($(APP_INTERFACE), APP_INTERFACE_VCP) 
    LIBDIRS += -L$(DRIVERS_PATH)/lib
  endif
  # sDDS lib dir
  LIBDIRS += -L$(SDDS_PATH)/lib

  LIBS = -l$(STACK_LIB) 
  ifeq ($(APP_INTERFACE), APP_INTERFACE_VCP) 
    LIBS += -l$(VCP_LIB) 
  endif
  LIBS += -l$(CS_LIB) 
  LIBS += -l$(PDS_LIB) 
  LIBS += -l$(BSP_LIB) 
  ifeq ($(APP_USE_OTAU), 1)
    LIBS += -l$(OTAU_SERVER_LIB) 
  endif
  LIBS += -l$(HAL_LIB)
  LIBS += -l$(STACK_LIB)
  # sDDS lib
  LIBS += -l$(SDDS_LIB)
endif # GCC
ifeq ($(COMPILER_TYPE), IAR)
  LIBS =  $(COMPONENTS_PATH)/../lib/lib$(HAL_LIB).a
  LIBS += $(COMPONENTS_PATH)/../lib/lib$(STACK_LIB).a
  LIBS += $(CS_PATH)/lib/lib$(CS_LIB).a
  LIBS += $(PDS_PATH)/lib/lib$(PDS_LIB).a
  LIBS += $(BSP_PATH)/lib/lib$(BSP_LIB).a
  ifeq ($(APP_USE_OTAU), 1)
    LIBDIRS += -L$(OTAU_SERVER_PATH)/lib/lib$(OTAU_SERVER_LIB).a
  endif
  ifeq ($(APP_INTERFACE), APP_INTERFACE_VCP) 
    LIBS += $(DRIVERS_PATH)/lib/lib$(VCP_LIB).a
  endif
endif # IAR

#==============================================================================
# Linking
#==============================================================================
ifeq ($(COMPILER_TYPE), GCC)
  EXECUTABLE_FORMAT = elf
  # It's easier to use indirect ld call via gcc instead of direct ld call.
  LD = $(CC)
  LINKER_FLAGS = -Xlinker -Map=$(APP_PATH)/list/$(PROJNAME).map -Wl,--gc-sections
  ifeq ($(HAL), ATMEGA1281)
    LINKER_FLAGS += $(filter -mmcu%,$(CFLAGS))
    LINKER_FLAGS += -Wl,--script=$(AVRSTUB_PATH)/linkerScr/atmega1281.ld
  endif
  ifeq ($(HAL), ATMEGA2561)
    LINKER_FLAGS += $(filter -mmcu%,$(CFLAGS))
    LINKER_FLAGS += -Wl,--script=$(AVRSTUB_PATH)/linkerScr/atmega2561.ld
  endif
  ifeq ($(HAL), ATMEGA1284)
    LINKER_FLAGS += $(filter -mmcu%,$(CFLAGS))
    LINKER_FLAGS += -Wl,--script=$(AVRSTUB_PATH)/linkerScr/atmega1284p.ld
  endif
  ifeq ($(HAL), AT90USB1287)
    LINKER_FLAGS += $(filter -mmcu%,$(CFLAGS))
    LINKER_FLAGS += -Wl,--script=$(AVRSTUB_PATH)/linkerScr/at90usb1287.ld
  endif
  ifeq ($(HAL), ATXMEGA128A1)
    LINKER_FLAGS += $(filter -mmcu%,$(CFLAGS))
    #LINKER_FLAGS += -Wl,--script=$(APP_PATH)/linkerScr/atxmega128a1.ld
  endif
  ifeq ($(HAL), ATXMEGA256A3)
    LINKER_FLAGS += $(filter -mmcu%,$(CFLAGS))
    #LINKER_FLAGS += -Wl,--script=$(APP_PATH)/linkerScr/atxmega256a3.ld
  endif
  ifeq ($(HAL), ATMEGA128RFA1)
    LINKER_FLAGS += $(filter -mmcu%,$(CFLAGS))
    LINKER_FLAGS += -Wl,--script=$(AVRSTUB_PATH)/linkerScr/atmega128rfa1.ld
    LINKER_FLAGS += -Wl,--section-start=.data=0x800200
  endif
  ifeq ($(HAL), AT91SAM7X256)
    LDSCRIPT = atmel-rom
    LINKER_FLAGS += $(filter -mthumb%,$(CFLAGS))
    LINKER_FLAGS += $(filter -mcpu%,$(CFLAGS))
    LINKER_FLAGS += -nostartfiles
    LINKER_FLAGS += -Xlinker -T$(AVRSTUB_PATH)/linkerScr/$(LDSCRIPT).ld
  endif
  ifeq ($(DEBUG), 1)
    LINKER_FLAGS += -g -O0
  endif
endif # GCC

ifeq ($(COMPILER_TYPE), IAR)
  ifeq ($(HAL), AT32UC3A0512)
    LINKER_FLAGS =  -rt 
    LINKER_FLAGS += -f $(APP_PATH)/linkerScr/lnkuc3a0512_cli.xcl
    LINKER_FLAGS += -s __program_start
    LINKER_FLAGS += $(IAR_PATH)/lib/dlavr32allasn.r82
  endif
  ifeq ($(HAL), AT91SAM7X256)
    EXECUTABLE_FORMAT = elf
    LDSCRIPT = at91SAM7X256_FLASH
    LINKER_FLAGS  = --redirect _Printf=_PrintfTiny 
    LINKER_FLAGS += --redirect _Scanf=_ScanfSmall
    LINKER_FLAGS += --semihosting 
    LINKER_FLAGS += --entry __iar_program_start
    LINKER_FLAGS += --map $(APP_PATH)/list/$(PROJNAME).map
    LINKER_FLAGS += --config $(APP_PATH)/linkerScr/$(LDSCRIPT).icf
  endif
  ifneq (, $(findstring $(HAL), ATMEGA1281 ATMEGA2561 ATXMEGA128A1 ATXMEGA256A3 ATMEGA1284 AT90USB1287 ATMEGA128RFA1))
    EXECUTABLE_FORMAT = hex
    #LINKER_FLAGS += -h"(CODE)0-(_..X_INTVEC_SIZE-1)"
    LINKER_FLAGS += -Fintel-extended
    LINKER_FLAGS += -l $(APP_PATH)/list/$(PROJNAME).html
    LINKER_FLAGS += -xmsh #Generate linker list file
    LINKER_FLAGS += -H1895
    LINKER_FLAGS += -S
    ifeq ($(HAL), ATMEGA1281)
      LINKER_FLAGS += -s __bitcloud_start $(IAR_PATH)/LIB/DLIB/dlAVR-3s-ec_mul-n.r90
      LINKER_FLAGS += -f $(APP_PATH)/linkerScr/cfgm1281bitcloud.xcl
      LINKER_FLAGS += -e_PrintfSmall=_Printf
    endif
    ifeq ($(HAL), ATMEGA2561)
      LINKER_FLAGS += -s __bitcloud_start $(IAR_PATH)/LIB/DLIB/dlAVR-3s-ec_mul-n.r90
      LINKER_FLAGS += -f $(APP_PATH)/linkerScr/cfgm2561bitcloud.xcl
      LINKER_FLAGS += -e_PrintfSmall=_Printf
    endif
    ifeq ($(HAL), ATXMEGA128A1)
      LINKER_FLAGS += -s __program_start $(IAR_PATH)/LIB/CLIB/cl6s-xmega.r90
      LINKER_FLAGS += -f $(APP_PATH)/linkerScr/cfgxm128a1.xcl
    endif
    ifeq ($(HAL), ATXMEGA256A3)
      LINKER_FLAGS += -s __program_start $(IAR_PATH)/LIB/DLIB/dlAVR-5s-xmega-n.r90
      LINKER_FLAGS += -f $(APP_PATH)/linkerScr/cfgxm256a3.xcl
    endif
    ifeq ($(HAL), ATMEGA1284)
      LINKER_FLAGS += -s __bitcloud_start $(IAR_PATH)/LIB/DLIB/dlAVR-3s-ec_mul-n.r90
      LINKER_FLAGS += -f $(APP_PATH)/linkerScr/cfgm1284bitcloud.xcl
      LINKER_FLAGS += -e_PrintfSmall=_Printf      
    endif
    ifeq ($(HAL), AT90USB1287)
      LINKER_FLAGS += -s __bitcloud_start $(IAR_PATH)/LIB/DLIB/dlAVR-3s-ec_mul-n.r90
      LINKER_FLAGS += -f $(APP_PATH)/linkerScr/cfgusb1287bitcloud.xcl
      LINKER_FLAGS += -e_PrintfSmall=_Printf      
    endif      
    ifeq ($(HAL), ATMEGA128RFA1)
      LINKER_FLAGS += -s __bitcloud_start $(IAR_PATH)/LIB/DLIB/dlAVR-3s-ec_mul-n.r90 
      LINKER_FLAGS += -f $(APP_PATH)/linkerScr/cfgm128rfa1bitcloud.xcl
      LINKER_FLAGS += -e_PrintfSmall=_Printf
    endif
  endif
endif # IAR

PLATFORM_SPECIFIC_OBJECTS_WITH_PATH = $(addprefix $(COMPONENTS_PATH)/../lib/, $(PLATFORM_SPECIFIC_OBJECTS))

#==============================================================================
# Export all variables needed by sub-make processes
#==============================================================================
export MAKERULES BOARD CFLAGS_HW CFLAGS_CS CFLAGS_DBG CFLAGS_BSP SDDS_LIB CFLAGS_SDDS APP_PATH

#==============================================================================
# Objects
#==============================================================================
SRCS = $(wildcard $(APP_PATH)/src/*.c)
SRCS += $(AVRSTUB_PATH)/BitCloud.c
SRCS += $(AVRSTUB_PATH)/BitCloud_sdds.c
SRCS += $(AVRSTUB_PATH)/WSNVisualizer.c
OBJS += $(addprefix $(APP_PATH)/objs/, $(notdir $(SRCS:.c=.o)))


#==============================================================================
# Targets
#==============================================================================
.PHONY: otauserver all clean size cs pds bsp vcp obj_label

all: otauserver $(PROJNAME).elf copyelf $(PROJNAME).srec $(PROJNAME).hex $(PROJNAME).bin size 
#all: otauserver $(PROJNAME).elf $(PROJNAME).srec $(PROJNAME).hex $(PROJNAME).bin size 


$(PROJNAME).elf: cs pds bsp vcp sdds obj_label $(OBJS) $(PLATFORM_SPECIFIC_OBJECTS_WITH_PATH)
	@echo 
	@echo -----------------Linking---------------------------
	$(LD) $(LIBDIRS) $(LINKER_FLAGS) $(OBJS) $(PLATFORM_SPECIFIC_OBJECTS_WITH_PATH) $(LIBS) -o $@

pds:
	make all -C $(PDS_PATH)

bsp:
	make all -C $(BSP_PATH)

cs:
	make all -C $(CS_PATH)

sdds:
	make all -C$(SDDS_PATH) -f Makefile.bitcloud

otauserver:
ifeq ($(APP_USE_OTAU), 1)
	make all -C $(OTAU_SERVER_PATH)
endif

vcp:
ifeq ($(APP_INTERFACE), APP_INTERFACE_VCP) 
	make all -C $(DRIVERS_PATH)/VCP
endif # APP_INTERFACE_VCP

obj_label:
	@echo 
	@echo -------Application objects creation---------------

$(APP_PATH)/objs/%.o: $(APP_PATH)/src/%.c
	$(CC) $(CFLAGS) $(INCLUDEDIRS) $< -o $@

$(APP_PATH)/objs/BitCloud.o: $(AVRSTUB_PATH)/BitCloud.c
	$(CC) $(CFLAGS) $(INCLUDEDIRS) $< -o $@

$(APP_PATH)/objs/BitCloud_sdds.o: $(AVRSTUB_PATH)/BitCloud_sdds.c
	$(CC) $(CFLAGS) $(INCLUDEDIRS) $< -o $@

$(APP_PATH)/objs/WSNVisualizer.o: $(AVRSTUB_PATH)/WSNVisualizer.c
	$(CC) $(CFLAGS) $(INCLUDEDIRS) $< -o $@

copyelf:$(PROJNAME).elf
#	cp $(PROJNAME).elf ~/Dropbox/sdds_elf/
	cp $(PROJNAME).elf test123.elf

%.srec: $(PROJNAME).elf
	$(OBJCOPY) -O srec --srec-len 128 $^ $@

%.hex:  $(PROJNAME).elf
	$(OBJCOPY) -O ihex -R .eeprom $^ $@

%.bin:  $(PROJNAME).elf
	$(OBJCOPY) -O binary --strip-debug --strip-unneeded -R .eeprom $^ $@

size: $(PROJNAME).elf
	@echo 
	@$(SIZE) -td $(PROJNAME).elf



clean:
	@echo 
	@echo -------Application cleaning------------------------
	-rm -rf $(OBJS) $(APP_PATH)/list/*.* $(PROJNAME).elf $(PROJNAME).hex $(PROJNAME).srec $(PROJNAME).bin
	make clean -C $(PDS_PATH)
	make clean -C $(CS_PATH)
	make clean -C $(BSP_PATH)
	make clean -C $(SDDS_PATH) -f Makefile.bitcloud
ifeq ($(APP_USE_OTAU), 1)
	make clean -C $(OTAU_SERVER_PATH)
endif
ifeq ($(APP_INTERFACE), APP_INTERFACE_VCP) 
	make clean -C $(DRIVERS_PATH)/VCP
endif # APP_INTERFACE_VCP

# eof Makefile
