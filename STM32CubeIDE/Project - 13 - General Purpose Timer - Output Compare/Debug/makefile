################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/User\ Drivers/Src/subdir.mk
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

BUILD_ARTIFACT_NAME := General Purpose Timer - Output Compare
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX := 
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME).$(BUILD_ARTIFACT_EXTENSION)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
General\ Purpose\ Timer\ -\ Output\ Compare.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
General\ Purpose\ Timer\ -\ Output\ Compare.list \

OBJCOPY_BIN += \
General\ Purpose\ Timer\ -\ Output\ Compare.bin \


# All Target
all: main-build

# Main-build Target
main-build: General\ Purpose\ Timer\ -\ Output\ Compare.elf secondary-outputs

# Tool invocations
General\ Purpose\ Timer\ -\ Output\ Compare.elf: $(OBJS) $(USER_OBJS) D:\temp\STM32TrainingExamplesRegisterLevel\STM32CubeIDE\Project\ -\ 13\ -\ General\ Purpose\ Timer\ -\ Output\ Compare\STM32F070RBTX_FLASH.ld
	arm-none-eabi-gcc -o "General Purpose Timer - Output Compare.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0 -T"D:\temp\STM32TrainingExamplesRegisterLevel\STM32CubeIDE\Project - 13 - General Purpose Timer - Output Compare\STM32F070RBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="General Purpose Timer - Output Compare.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

General\ Purpose\ Timer\ -\ Output\ Compare.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "General Purpose Timer - Output Compare.list"
	@echo 'Finished building: $@'
	@echo ' '

General\ Purpose\ Timer\ -\ Output\ Compare.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "General Purpose Timer - Output Compare.bin"
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
