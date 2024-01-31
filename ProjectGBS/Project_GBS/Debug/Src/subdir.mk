################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/ESP_DATA_HANDLER.c \
../Src/NMEA.c \
../Src/i2c_lcd.c \
../Src/keypad4x4.c \
../Src/main.c \
../Src/stm32f10x_it.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/uartRingBuffer.c 

OBJS += \
./Src/ESP_DATA_HANDLER.o \
./Src/NMEA.o \
./Src/i2c_lcd.o \
./Src/keypad4x4.o \
./Src/main.o \
./Src/stm32f10x_it.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/uartRingBuffer.o 

C_DEPS += \
./Src/ESP_DATA_HANDLER.d \
./Src/NMEA.d \
./Src/i2c_lcd.d \
./Src/keypad4x4.d \
./Src/main.d \
./Src/stm32f10x_it.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/uartRingBuffer.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I../Inc -I"D:/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/CMSIS/CM3/CoreSupport" -I"D:/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x" -I"D:/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/ESP_DATA_HANDLER.d ./Src/ESP_DATA_HANDLER.o ./Src/ESP_DATA_HANDLER.su ./Src/NMEA.d ./Src/NMEA.o ./Src/NMEA.su ./Src/i2c_lcd.d ./Src/i2c_lcd.o ./Src/i2c_lcd.su ./Src/keypad4x4.d ./Src/keypad4x4.o ./Src/keypad4x4.su ./Src/main.d ./Src/main.o ./Src/main.su ./Src/stm32f10x_it.d ./Src/stm32f10x_it.o ./Src/stm32f10x_it.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/uartRingBuffer.d ./Src/uartRingBuffer.o ./Src/uartRingBuffer.su

.PHONY: clean-Src

