################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32f303xc.s 

OBJS += \
./startup/startup_stm32f303xc.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo %cd%
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -I"E:/stm32f3discovery_hal_lib" -I"F:/Users/Bernd/Onedrive/Schule/4. Jahrgang/SYT/workspace/stm32f3discovery_hal_lib/Utilities/STM32F3-Discovery" -I"F:/Users/Bernd/Onedrive/Schule/4. Jahrgang/SYT/workspace/stm32f3discovery_hal_lib/Utilities/Components/lsm303dlhc" -I"F:/Users/Bernd/Onedrive/Schule/4. Jahrgang/SYT/workspace/stm32f3discovery_hal_lib/Utilities/Components/l3gd20" -I"F:/Users/Bernd/Onedrive/Schule/4. Jahrgang/SYT/workspace/stm32f3discovery_hal_lib/Utilities/Components/Common" -I"F:/Users/Bernd/Onedrive/Schule/4. Jahrgang/SYT/workspace/stm32f3discovery_hal_lib/HAL_Driver/Inc" -I"F:/Users/Bernd/Onedrive/Schule/4. Jahrgang/SYT/workspace/stm32f3discovery_hal_lib/HAL_Driver/Inc/Legacy" -I"F:/Users/Bernd/Onedrive/Schule/4. Jahrgang/SYT/workspace/stm32f3discovery_hal_lib/CMSIS/device" -I"F:/Users/Bernd/Onedrive/Schule/4. Jahrgang/SYT/workspace/stm32f3discovery_hal_lib/CMSIS/core" -I"E:/blinkLEDs/inc" -I"E:/stm32f3discovery_hal_lib/CMSIS/core" -I"E:/stm32f3discovery_hal_lib/CMSIS/device" -I"E:/stm32f3discovery_hal_lib/HAL_Driver/Inc/Legacy" -I"E:/stm32f3discovery_hal_lib/HAL_Driver/Inc" -I"E:/stm32f3discovery_hal_lib/Utilities/Components/Common" -I"E:/stm32f3discovery_hal_lib/Utilities/Components/l3gd20" -I"E:/stm32f3discovery_hal_lib/Utilities/Components/lsm303dlhc" -I"E:/stm32f3discovery_hal_lib/Utilities/STM32F3-Discovery" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


