################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/stm32f3xx_it.c \
../src/syscalls.c \
../src/system_stm32f3xx.c 

OBJS += \
./src/main.o \
./src/stm32f3xx_it.o \
./src/syscalls.o \
./src/system_stm32f3xx.o 

C_DEPS += \
./src/main.d \
./src/stm32f3xx_it.d \
./src/syscalls.d \
./src/system_stm32f3xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -DSTM32F30 -DSTM32F3DISCOVERY -DSTM32F3 -DSTM32F303VCTx -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -I"F:/Users/Bernd/Onedrive/Schule/Jahrgang_4/SYT/workspace/static_libary" -I"F:/Users/Bernd/Onedrive/Schule/Jahrgang_4/SYT/workspace/static_libary/inc" -I"F:/Users/Bernd/Onedrive/Schule/4. Jahrgang/SYT/workspace/stm32f3discovery_hal_lib/CMSIS/core" -I"F:/Users/Bernd/Onedrive/Schule/4. Jahrgang/SYT/workspace/stm32f3discovery_hal_lib/CMSIS/device" -I"F:/Users/Bernd/Onedrive/Schule/4. Jahrgang/SYT/workspace/stm32f3discovery_hal_lib/HAL_Driver/Inc/Legacy" -I"F:/Users/Bernd/Onedrive/Schule/4. Jahrgang/SYT/workspace/stm32f3discovery_hal_lib/HAL_Driver/Inc" -I"F:/Users/Bernd/Onedrive/Schule/4. Jahrgang/SYT/workspace/stm32f3discovery_hal_lib/Utilities/Components/Common" -I"F:/Users/Bernd/Onedrive/Schule/4. Jahrgang/SYT/workspace/stm32f3discovery_hal_lib/Utilities/Components/l3gd20" -I"F:/Users/Bernd/Onedrive/Schule/4. Jahrgang/SYT/workspace/stm32f3discovery_hal_lib/Utilities/Components/lsm303dlhc" -I"F:/Users/Bernd/Onedrive/Schule/4. Jahrgang/SYT/workspace/stm32f3discovery_hal_lib/Utilities/STM32F3-Discovery" -I"F:/Users/Bernd/Onedrive/Schule/Jahrgang_4/SYT/workspace/stm32f3discovery_hal_lib" -I"F:/Users/Bernd/Onedrive/Schule/Jahrgang_4/SYT/workspace/L07/inc" -I"F:/Users/Bernd/Onedrive/Schule/Jahrgang_4/SYT/workspace/stm32f3discovery_hal_lib/CMSIS/core" -I"F:/Users/Bernd/Onedrive/Schule/Jahrgang_4/SYT/workspace/stm32f3discovery_hal_lib/CMSIS/device" -I"F:/Users/Bernd/Onedrive/Schule/Jahrgang_4/SYT/workspace/stm32f3discovery_hal_lib/HAL_Driver/Inc/Legacy" -I"F:/Users/Bernd/Onedrive/Schule/Jahrgang_4/SYT/workspace/stm32f3discovery_hal_lib/HAL_Driver/Inc" -I"F:/Users/Bernd/Onedrive/Schule/Jahrgang_4/SYT/workspace/stm32f3discovery_hal_lib/Utilities/Components/Common" -I"F:/Users/Bernd/Onedrive/Schule/Jahrgang_4/SYT/workspace/stm32f3discovery_hal_lib/Utilities/Components/l3gd20" -I"F:/Users/Bernd/Onedrive/Schule/Jahrgang_4/SYT/workspace/stm32f3discovery_hal_lib/Utilities/Components/lsm303dlhc" -I"F:/Users/Bernd/Onedrive/Schule/Jahrgang_4/SYT/workspace/stm32f3discovery_hal_lib/Utilities/STM32F3-Discovery" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


