################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: L06.elf

dependents:
	-cd F:/Users/Bernd/Onedrive/Schule/Jahrgang_4/SYT/workspace/stm32f3discovery_hal_lib/Debug && $(MAKE) all
	-cd F:/Users/Bernd/Onedrive/Schule/Jahrgang_4/SYT/workspace/static_libary/Debug && $(MAKE) all

# Tool invocations
L06.elf: $(OBJS) $(USER_OBJS) F:/Users/Bernd/Onedrive/Schule/Jahrgang_4/SYT/workspace/stm32f3discovery_hal_lib/Debug/libstm32f3discovery_hal_lib.a F:/Users/Bernd/Onedrive/Schule/Jahrgang_4/SYT/workspace/static_libary/Debug/libstatic_libary.a
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -L"F:\Users\Bernd\Onedrive\Schule\Jahrgang_4\SYT\workspace\static_libary\Debug" -L"F:\Users\Bernd\Onedrive\Schule\Jahrgang_4\SYT\workspace\stm32f3discovery_hal_lib\Debug" -T"F:\Users\Bernd\Onedrive\Schule\Jahrgang_4\SYT\workspace\L06\LinkerScript.ld" -Wl,-Map=output.map -Wl,--gc-sections -lm -o "L06.elf" @"objects.list" $(USER_OBJS) $(LIBS) -u HAL_ADCEx_InjectedStart
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating binary and Printing size information:'
	arm-none-eabi-objcopy -O binary "L06.elf" "L06.bin"
	arm-none-eabi-size "L06.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
F:/Users/Bernd/Onedrive/Schule/Jahrgang_4/SYT/workspace/stm32f3discovery_hal_lib/Debug/libstm32f3discovery_hal_lib.a:
F:/Users/Bernd/Onedrive/Schule/Jahrgang_4/SYT/workspace/static_libary/Debug/libstatic_libary.a:

-include ../makefile.targets
