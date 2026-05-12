################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F0xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
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

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Project - 17 - ADC -Single Conversion with Interrupt
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Project\ -\ 17\ -\ ADC\ -Single\ Conversion\ with\ Interrupt.elf \

MAP_FILES += \
Project\ -\ 17\ -\ ADC\ -Single\ Conversion\ with\ Interrupt.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Project\ -\ 17\ -\ ADC\ -Single\ Conversion\ with\ Interrupt.list \


# All Target
all: main-build

# Main-build Target
main-build: Project\ -\ 17\ -\ ADC\ -Single\ Conversion\ with\ Interrupt.elf secondary-outputs

# Tool invocations
Project\ -\ 17\ -\ ADC\ -Single\ Conversion\ with\ Interrupt.elf Project\ -\ 17\ -\ ADC\ -Single\ Conversion\ with\ Interrupt.map: $(OBJS) $(USER_OBJS) D:\stm32_workspace\STM32TrainingExamplesRegisterLevel\STM32CubeIDE\Project\ -\ 17\ -\ ADC\ -Single\ Conversion\ with\ Interrupt\STM32F070RBTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Project - 17 - ADC -Single Conversion with Interrupt.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0 -T"D:\stm32_workspace\STM32TrainingExamplesRegisterLevel\STM32CubeIDE\Project - 17 - ADC -Single Conversion with Interrupt\STM32F070RBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Project - 17 - ADC -Single Conversion with Interrupt.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Project\ -\ 17\ -\ ADC\ -Single\ Conversion\ with\ Interrupt.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Project - 17 - ADC -Single Conversion with Interrupt.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Project\ -\ 17\ -\ ADC\ -Single\ Conversion\ with\ Interrupt.elf Project\ -\ 17\ -\ ADC\ -Single\ Conversion\ with\ Interrupt.list Project\ -\ 17\ -\ ADC\ -Single\ Conversion\ with\ Interrupt.map Project\\ -\\ 17\\ -\\ ADC\\ -Single\\ Conversion\\ with\\ Interrupt.elf default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
