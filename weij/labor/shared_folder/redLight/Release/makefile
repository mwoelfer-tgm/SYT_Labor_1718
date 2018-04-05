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
all: redLight.elf

dependents:
	-cd F:/Users/Bernd/Onedrive/Schule/4.\ Jahrgang/SYT/workspace/stm32f3discovery_hal_lib/Release && $(MAKE) all

# Tool invocations
redLight.elf: $(OBJS) $(USER_OBJS) F:/Users/Bernd/Onedrive/Schule/4.\ Jahrgang/SYT/workspace/stm32f3discovery_hal_lib/Release/libstm32f3discovery_hal_lib.a
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -L"F:\Users\Bernd\Onedrive\Schule\4. Jahrgang\SYT\workspace\stm32f3discovery_hal_lib\Release" -T"F:\Users\Bernd\Onedrive\Schule\4. Jahrgang\SYT\workspace\redLight\LinkerScript.ld" -Wl,-Map=output.map -Wl,--gc-sections -lm -o "redLight.elf" @"objects.list" $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating binary and Printing size information:'
	arm-none-eabi-objcopy -O binary "redLight.elf" "redLight.bin"
	arm-none-eabi-size -B "redLight.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
F:/Users/Bernd/Onedrive/Schule/4.\ Jahrgang/SYT/workspace/stm32f3discovery_hal_lib/Release/libstm32f3discovery_hal_lib.a:

-include ../makefile.targets
