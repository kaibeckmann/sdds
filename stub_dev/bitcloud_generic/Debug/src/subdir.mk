################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/WSNCoord.c \
../src/WSNDemoApp.c \
../src/WSNEndDevice.c \
../src/WSNRouter.c \
../src/WSNSensorManager.c \
../src/WSNUARTManager.c \
../src/WSNVisualizer.c 

OBJS += \
./src/WSNCoord.o \
./src/WSNDemoApp.o \
./src/WSNEndDevice.o \
./src/WSNRouter.o \
./src/WSNSensorManager.o \
./src/WSNUARTManager.o \
./src/WSNVisualizer.o 

C_DEPS += \
./src/WSNCoord.d \
./src/WSNDemoApp.d \
./src/WSNEndDevice.d \
./src/WSNRouter.d \
./src/WSNSensorManager.d \
./src/WSNUARTManager.d \
./src/WSNVisualizer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega1284p -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


