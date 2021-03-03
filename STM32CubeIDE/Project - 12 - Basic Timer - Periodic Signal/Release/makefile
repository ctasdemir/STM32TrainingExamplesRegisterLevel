################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F0xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

BUILD_ARTIFACT_NAME := Basic Timer - Periodic Signal
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX := 
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME).$(BUILD_ARTIFACT_EXTENSION)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Basic\ Timer\ -\ Periodic\ Signal.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Basic\ Timer\ -\ Periodic\ Signal.list \

OBJCOPY_BIN += \
Basic\ Timer\ -\ Periodic\ Signal.bin \


# All Target
all: main-build

# Main-build Target
main-build: Basic\ Timer\ -\ Periodic\ Signal.elf secondary-outputs

# Tool invocations
Basic\ Timer\ -\ Periodic\ Signal.elf: $(OBJS) $(USER_OBJS) D:\workspace\Basic\ Timer\ -\ Periodic\ Signal\STM32F070RBTX_FLASH.ld
	arm-none-eabi-gcc -o "Basic Timer - Periodic Signal.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0 -T"D:\workspace\Basic Timer - Periodic Signal\STM32F070RBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Basic Timer - Periodic Signal.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Basic\ Timer\ -\ Periodic\ Signal.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Basic Timer - Periodic Signal.list"
	@echo 'Finished building: $@'
	@echo ' '

Basic\ Timer\ -\ Periodic\ Signal.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Basic Timer - Periodic Signal.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified
.SECONDARY:

-include ../makefile.targets
