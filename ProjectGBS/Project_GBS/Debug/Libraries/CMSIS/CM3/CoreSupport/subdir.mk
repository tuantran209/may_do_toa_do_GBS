################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/CMSIS/CM3/CoreSupport/core_cm3.c 

OBJS += \
./Libraries/CMSIS/CM3/CoreSupport/core_cm3.o 

C_DEPS += \
./Libraries/CMSIS/CM3/CoreSupport/core_cm3.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/CMSIS/CM3/CoreSupport/core_cm3.o: D:/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/CMSIS/CM3/CoreSupport/core_cm3.c Libraries/CMSIS/CM3/CoreSupport/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I../Inc -I"D:/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/CMSIS/CM3/CoreSupport" -I"D:/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x" -I"D:/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Libraries-2f-CMSIS-2f-CM3-2f-CoreSupport

clean-Libraries-2f-CMSIS-2f-CM3-2f-CoreSupport:
	-$(RM) ./Libraries/CMSIS/CM3/CoreSupport/core_cm3.d ./Libraries/CMSIS/CM3/CoreSupport/core_cm3.o ./Libraries/CMSIS/CM3/CoreSupport/core_cm3.su

.PHONY: clean-Libraries-2f-CMSIS-2f-CM3-2f-CoreSupport

