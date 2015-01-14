######################################################################################
# GNU GCC ARM Embeded Toolchain base directories and binaries 
######################################################################################
GCC_BASE = /home/tkcov/cross/gcc-arm-none-eabi-4_7-2014q2/
GCC_BIN  = $(GCC_BASE)bin/
GCC_LIB  = $(GCC_BASE)arm-none-eabi/lib/
GCC_INC  = $(GCC_BASE)arm-none-eabi/include/

TRGT = arm-none-eabi-
AS       = $(TRGT)as
CC       = $(TRGT)gcc
CPP      = $(TRGT)g++
LD       = $(TRGT)gcc
OBJCOPY  = $(TRGT)objcopy
SZ	 = $(TRGT)size


######################################################################################
# Custom options for cortex-m and cortex-r processors 
######################################################################################
CORTEX_M0PLUS_CC_FLAGS  = -mthumb -mcpu=cortex-m0plus
CORTEX_M0PLUS_LIB_PATH  = $(GCC_LIB)armv6-m
CORTEX_M0_CC_FLAGS      = -mthumb -mcpu=cortex-m0
CORTEX_M0_LIB_PATH      = $(GCC_LIB)armv6-m
CORTEX_M1_CC_FLAGS      = -mthumb -mcpu=cortex-m1
CORTEX_M1_LIB_PATH      = $(GCC_LIB)armv6-m
CORTEX_M3_CC_FLAGS      = -mthumb -mcpu=cortex-m3
CORTEX_M3_LIB_PATH      = $(GCC_LIB)armv7-m
CORTEX_M4_NOFP_CC_FLAGS = -mthumb -mcpu=cortex-m4
CORTEX_M4_NOFP_LIB_PATH = $(GCC_LIB)armv7e-m
CORTEX_M4_SWFP_CC_FLAGS = -mthumb -mcpu=cortex-m4 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
CORTEX_M4_SWFP_LIB_PATH = $(GCC_LIB)armv7e-m/softfp
CORTEX_M4_HWFP_CC_FLAGS = -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
CORTEX_M4_HWFP_LIB_PATH = $(GCC_LIB)armv7e-m/fpu
CORTEX_R4_NOFP_CC_FLAGS = -mthumb -march=armv7-r
CORTEX_R4_NOFP_LIB_PATH = $(GCC_LIB)armv7-r/thumb
CORTEX_R4_SWFP_CC_FLAGS = -mthumb -march=armv7-r -mfloat-abi=softfp -mfloat-abi=softfp -mfpu=vfpv3-d16
CORTEX_R4_SWFP_LIB_PATH = $(GCC_LIB)armv7-r/thumb/softfp
CORTEX_R4_HWFP_CC_FLAGS = -mthumb -march=armv7-r -mfloat-abi=softfp -mfloat-abi=hard -mfpu=vfpv3-d16
CORTEX_R4_HWFP_LIB_PATH = $(GCC_LIB)armv7-r/thumb/fpu
CORTEX_R5_NOFP_CC_FLAGS = -mthumb -march=armv7-r
CORTEX_R5_NOFP_LIB_PATH = $(GCC_LIB)armv7-r/thumb
CORTEX_R5_SWFP_CC_FLAGS = -mthumb -march=armv7-r -mfloat-abi=softfp -mfloat-abi=softfp -mfpu=vfpv3-d16
CORTEX_R5_SWFP_LIB_PATH = $(GCC_LIB)armv7-r/thumb/softfp
CORTEX_R5_HWFP_CC_FLAGS = -mthumb -march=armv7-r -mfloat-abi=softfp -mfloat-abi=hard -mfpu=vfpv3-d16
CORTEX_R5_HWFP_LIB_PATH = $(GCC_LIB)armv7-r/thumb/fpu

######################################################################################
# Location of STM32 HAL libraries and drivers
######################################################################################

STM32DRIVERDIR = ./Drivers
HAL_DIR = $(STM32DRIVERDIR)/STM32F4xx_HAL_Driver
CMSIS_DIR = $(STM32DRIVERDIR)/CMSIS

DEVICE = STM32F4xx
MCU = STM32F415xx

DRIVER_DIR = $(HAL_DIR)/Src
DRIVER_SOURCES = $(DRIVER_DIR)/stm32f4xx_hal_adc.c \
	$(DRIVER_DIR)/stm32f4xx_hal_adc_ex.c \
	$(DRIVER_DIR)/stm32f4xx_hal.c \
	$(DRIVER_DIR)/stm32f4xx_hal_can.c \
	$(DRIVER_DIR)/stm32f4xx_hal_cortex.c \
	$(DRIVER_DIR)/stm32f4xx_hal_crc.c \
	$(DRIVER_DIR)/stm32f4xx_hal_cryp.c \
	$(DRIVER_DIR)/stm32f4xx_hal_cryp_ex.c \
	$(DRIVER_DIR)/stm32f4xx_hal_dac.c \
	$(DRIVER_DIR)/stm32f4xx_hal_dac_ex.c \
	$(DRIVER_DIR)/stm32f4xx_hal_dcmi.c \
	$(DRIVER_DIR)/stm32f4xx_hal_dma2d.c \
	$(DRIVER_DIR)/stm32f4xx_hal_dma.c \
	$(DRIVER_DIR)/stm32f4xx_hal_dma_ex.c \
	$(DRIVER_DIR)/stm32f4xx_hal_eth.c \
	$(DRIVER_DIR)/stm32f4xx_hal_flash.c \
	$(DRIVER_DIR)/stm32f4xx_hal_flash_ex.c \
	$(DRIVER_DIR)/stm32f4xx_hal_flash_ramfunc.c \
	$(DRIVER_DIR)/stm32f4xx_hal_gpio.c \
	$(DRIVER_DIR)/stm32f4xx_hal_hash.c \
	$(DRIVER_DIR)/stm32f4xx_hal_hash_ex.c \
	$(DRIVER_DIR)/stm32f4xx_hal_hcd.c \
	$(DRIVER_DIR)/stm32f4xx_hal_i2c.c \
	$(DRIVER_DIR)/stm32f4xx_hal_i2c_ex.c \
	$(DRIVER_DIR)/stm32f4xx_hal_i2s.c \
	$(DRIVER_DIR)/stm32f4xx_hal_i2s_ex.c \
	$(DRIVER_DIR)/stm32f4xx_hal_irda.c \
	$(DRIVER_DIR)/stm32f4xx_hal_iwdg.c \
	$(DRIVER_DIR)/stm32f4xx_hal_ltdc.c \
	$(DRIVER_DIR)/stm32f4xx_hal_nand.c \
	$(DRIVER_DIR)/stm32f4xx_hal_nor.c \
	$(DRIVER_DIR)/stm32f4xx_hal_pccard.c \
	$(DRIVER_DIR)/stm32f4xx_hal_pcd.c \
	$(DRIVER_DIR)/stm32f4xx_hal_pcd_ex.c \
	$(DRIVER_DIR)/stm32f4xx_hal_pwr.c \
	$(DRIVER_DIR)/stm32f4xx_hal_pwr_ex.c \
	$(DRIVER_DIR)/stm32f4xx_hal_rcc.c \
	$(DRIVER_DIR)/stm32f4xx_hal_rcc_ex.c \
	$(DRIVER_DIR)/stm32f4xx_hal_rng.c \
	$(DRIVER_DIR)/stm32f4xx_hal_rtc.c \
	$(DRIVER_DIR)/stm32f4xx_hal_rtc_ex.c \
	$(DRIVER_DIR)/stm32f4xx_hal_sai.c \
	$(DRIVER_DIR)/stm32f4xx_hal_sd.c \
	$(DRIVER_DIR)/stm32f4xx_hal_sdram.c \
	$(DRIVER_DIR)/stm32f4xx_hal_smartcard.c \
	$(DRIVER_DIR)/stm32f4xx_hal_spi.c \
	$(DRIVER_DIR)/stm32f4xx_hal_sram.c \
	$(DRIVER_DIR)/stm32f4xx_hal_tim.c \
	$(DRIVER_DIR)/stm32f4xx_hal_tim_ex.c \
	$(DRIVER_DIR)/stm32f4xx_hal_uart.c \
	$(DRIVER_DIR)/stm32f4xx_hal_usart.c \
	$(DRIVER_DIR)/stm32f4xx_hal_wwdg.c \
	$(DRIVER_DIR)/stm32f4xx_ll_fmc.c \
	$(DRIVER_DIR)/stm32f4xx_ll_fsmc.c \
	$(DRIVER_DIR)/stm32f4xx_ll_sdmmc.c \
	$(DRIVER_DIR)/stm32f4xx_ll_usb.c 

DRIVER_OBJS = $(DRIVER_SOURCES:%.c=%.o)

FREERTOS_DIR = ./Middlewares/Third_Party/FreeRTOS/Source
FREERTOS_INC = -I$(FREERTOS_DIR)/include -I$(FREERTOS_DIR)/CMSIS_RTOS \
	-I$(FREERTOS_DIR)/portable/GCC/ARM_CM4F

FREERTOS_SRCS = $(FREERTOS_DIR)/croutine.c \
	$(FREERTOS_DIR)/list.c \
	$(FREERTOS_DIR)/queue.c \
	$(FREERTOS_DIR)/tasks.c \
	$(FREERTOS_DIR)/timers.c \
	$(FREERTOS_DIR)/CMSIS_RTOS/cmsis_os.c \
	$(FREERTOS_DIR)/portable/GCC/ARM_CM4F/port.c \
	$(FREERTOS_DIR)/portable/MemMang/heap_2.c

FREERTOS_OBJS = $(FREERTOS_SRCS:%.c=%.o)

I2CPERIPH_PATH = ./I2CPeripherals
I2CPERIPH_INC = -I$(I2CPERIPH_PATH)
I2CPERIPH_SRCS = $(I2CPERIPH_PATH)/ioext.cpp
I2CPERIPH_OBJS = $(I2CPERIPH_SRCS:%.cpp=%.o)

UTILITY_PATH = ./Utility
UTILITY_INC = -I$(UTILITY_PATH)
UTILITY_SRC = $(UTILITY_PATH)/delay.c \
	$(UTILITY_PATH)/syscalls.c \
	$(UTILITY_PATH)/serial.c \
	$(UTILITY_PATH)/shell.c \
	$(UTILITY_PATH)/utility.c
	
UTILITY_OBJS = $(UTILITY_SRC:%.c=%.o)	
	

FATFS_DIR = ./Middlewares/Third_Party/FatFs/src
FATFS_INC = -I$(FATFS_DIR)
FATFS_SRC = $(FATFS_DIR)/ff.c \
	$(FATFS_DIR)/diskio.c \
	$(FATFS_DIR)/ff_gen_drv.c \
	$(FATFS_DIR)/option/unicode.c

FATFS_OBJS = $(FATFS_SRC:%.c=%.o)

PROJECT_SRCS =  \
	Src/freertos.c \
	Src/gpio.c \
	Src/iwdg.c \
	Src/dma.c \
	Src/crc.c \
	Src/stm32f4xx_hal_msp.c \
	Src/stm32f4xx_it.c \
	Src/tim.c \
	Src/usart.c \
	Src/usb_otg.c \
	Src/user_diskio.c \
	Src/system_stm32f4xx.c

PROJECT_OBJS = $(PROJECT_SRCS:%.c=%.o)
STARTUP_OBJS = Src/startup_stm32f415xx.o

PROJECT_CPP_SRCS = \
	Src/i2c.cpp \
	Src/sharedi2c.cpp \
	Src/spi.cpp \
	Src/main.cpp

PROJECT_CPP_OBJS = $(PROJECT_CPP_SRCS:%.cpp=%.o)


######################################################################################
# Main makefile project configuration
#    PROJECT      = <name of the target to be built>
#    MCU_CC_FLAGS = <one of the CC_FLAGS above>
#    MCU_LIB_PATH = <one of the LIB_PATH above>
#    OPTIMIZE_FOR = < SIZE or nothing >
#    DEBUG_LEVEL  = < -g compiler option or nothing >
#    OPTIM_LEVEL  = < -O compiler option or nothing >
######################################################################################
PROJECT           = simple
MCU_CC_FLAGS      = $(CORTEX_M4_HWFP_CC_FLAGS) -D$(MCU)
MCU_LIB_PATH      = $(CORTEX_M4_HWFP_LIB_PATH)
OPTIMIZE_FOR      = 
DEBUG_LEVEL       = 
OPTIM_LEVEL       = 
LINKER_SCRIPT     = ./STM32F415RG_FLASH.ld


PROJECT_INC_PATHS = -I./Inc -I$(HAL_DIR)/Inc -I$(CMSIS_DIR)/Device/ST/$(DEVICE)/Include -I$(CMSIS_DIR)/Include 
PROJECT_LIB_PATHS = -L. 
PROJECT_LIBRARIES =
PROJECT_SYMBOLS   = -DTOOLCHAIN_GCC_ARM -DNO_RELOC='0'  


######################################################################################
# Main makefile system configuration
######################################################################################
SYS_OBJECTS = 
SYS_INC_PATHS = -I. -I$(GCC_INC) 
SYS_LIB_PATHS = -L$(MCU_LIB_PATH)
ifeq (OPTIMIZE_FOR, SIZE)
SYS_LIBRARIES = -lstdc++_s -lsupc++_s -lm -lc_s -lg_s -lnosys
SYS_LD_FLAGS  = --specs=nano.specs -u _printf_float -u _scanf_float
else 
SYS_LIBRARIES = -lstdc++ -lsupc++ -lm -lc -lg -lnosys
SYS_LD_FLAGS  = 
endif


############################################################################### 
# Command line building
###############################################################################
ifdef DEBUG_LEVEL
CC_DEBUG_FLAGS = -g$(DEBUG_LEVEL)
CC_SYMBOLS = -DDEBUG $(PROJECT_SYMBOLS)
else
CC_DEBUG_FLAGS =
CC_SYMBOLS = -DNODEBUG $(PROJECT_SYMBOLS)
endif 

ifdef OPTIM_LEVEL
CC_OPTIM_FLAGS = -O$(OPTIM_LEVEL)
else 
CC_OPTIM_FLAGS = 
endif

INCLUDE_PATHS = $(PROJECT_INC_PATHS) $(SYS_INC_PATHS) $(FREERTOS_INC) $(FATFS_INC) $(I2CPERIPH_INC) $(UTILITY_INC)
LIBRARY_PATHS = $(PROJECT_LIB_PATHS) $(SYS_LIB_PATHS)
CC_FLAGS = $(MCU_CC_FLAGS) -c $(CC_OPTIM_FLAGS) $(CC_DEBUG_FLAGS) -fno-common -fmessage-length=0 -Wall -fno-exceptions -ffunction-sections -fdata-sections 
LD_FLAGS = $(MCU_CC_FLAGS) -Wl,--gc-sections $(SYS_LD_FLAGS) -Wl,-Map=$(PROJECT).map 
LD_SYS_LIBS = $(SYS_LIBRARIES)

BULD_TARGET = $(PROJECT)


############################################################################### 
# Makefile execution
###############################################################################

all: $(BULD_TARGET).bin $(BULD_TARGET).hex

clean:
	rm -f $(BULD_TARGET).bin $(BULD_TARGET).elf $(PROJECT_OBJS) $(PROJECT_CPP_OBJS) $(DRIVER_OBJS) $(FREERTOS_OBJS) $(FATFS_OBJS) $(STARTUP_OBJS) \
		$(I2CPERIPH_OBJS) $(UTILITY_OBJS) *.hex *.map 

%.o:%.s
	@echo "Compiling startup file $< ..."
	@$(AS) $(CORTEX_M4_HWFP_CC_FLAGS) -o $@ $<

%.o:%.c
	@echo "$<"
	@$(CC)  $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu99   $(INCLUDE_PATHS) -o $@ $<

%.o:%.cpp
	@echo "$<"
	@$(CPP) $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu++98 $(INCLUDE_PATHS) -o $@ $<


$(BULD_TARGET).elf:  $(SYS_OBJECTS) $(DRIVER_OBJS) $(FREERTOS_OBJS) $(FATFS_OBJS) $(I2CPERIPH_OBJS) $(UTILITY_OBJS) $(PROJECT_OBJS) $(PROJECT_CPP_OBJS) $(STARTUP_OBJS)
	@$(LD) $(LD_FLAGS) -T$(LINKER_SCRIPT) $(LIBRARY_PATHS) -o $@ $^ $(PROJECT_LIBRARIES) $(SYS_LIBRARIES) $(PROJECT_LIBRARIES) $(SYS_LIBRARIES)
	@echo "Binary sections sizes ..."
	@$(SZ) -d $@

$(BULD_TARGET).bin: $(BULD_TARGET).elf
	@echo "Creating bin format... $@"
	@$(OBJCOPY) -O binary $< $@

$(BULD_TARGET).hex: $(BULD_TARGET).elf
	@echo "Creating hex format... $@"
	@$(OBJCOPY) -O ihex $< $@

