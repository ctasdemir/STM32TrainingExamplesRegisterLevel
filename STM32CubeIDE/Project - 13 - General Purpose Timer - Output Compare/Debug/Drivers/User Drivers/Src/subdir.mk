################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/stm32_workspace/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User\ Drivers/Src/adc_int_driver.c \
D:/stm32_workspace/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User\ Drivers/Src/adc_sequence_driver.c \
D:/stm32_workspace/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User\ Drivers/Src/button_driver.c \
D:/stm32_workspace/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User\ Drivers/Src/button_exti_driver.c \
D:/stm32_workspace/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User\ Drivers/Src/led_driver.c \
D:/stm32_workspace/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User\ Drivers/Src/pwm_driver.c \
D:/stm32_workspace/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User\ Drivers/Src/servo_driver.c \
D:/stm32_workspace/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User\ Drivers/Src/timer14_driver.c \
D:/stm32_workspace/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User\ Drivers/Src/timer6_driver.c \
D:/stm32_workspace/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User\ Drivers/Src/uart_driver.c 

OBJS += \
./Drivers/User\ Drivers/Src/adc_int_driver.o \
./Drivers/User\ Drivers/Src/adc_sequence_driver.o \
./Drivers/User\ Drivers/Src/button_driver.o \
./Drivers/User\ Drivers/Src/button_exti_driver.o \
./Drivers/User\ Drivers/Src/led_driver.o \
./Drivers/User\ Drivers/Src/pwm_driver.o \
./Drivers/User\ Drivers/Src/servo_driver.o \
./Drivers/User\ Drivers/Src/timer14_driver.o \
./Drivers/User\ Drivers/Src/timer6_driver.o \
./Drivers/User\ Drivers/Src/uart_driver.o 

C_DEPS += \
./Drivers/User\ Drivers/Src/adc_int_driver.d \
./Drivers/User\ Drivers/Src/adc_sequence_driver.d \
./Drivers/User\ Drivers/Src/button_driver.d \
./Drivers/User\ Drivers/Src/button_exti_driver.d \
./Drivers/User\ Drivers/Src/led_driver.d \
./Drivers/User\ Drivers/Src/pwm_driver.d \
./Drivers/User\ Drivers/Src/servo_driver.d \
./Drivers/User\ Drivers/Src/timer14_driver.d \
./Drivers/User\ Drivers/Src/timer6_driver.d \
./Drivers/User\ Drivers/Src/uart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/User\ Drivers/Src/adc_int_driver.o: ../Drivers/User\ Drivers/Src/adc_int_driver.c Drivers/User\ Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F070xB -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I"../../User Drivers/Inc" -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/User Drivers/Src/adc_int_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/User\ Drivers/Src/adc_sequence_driver.o: ../Drivers/User\ Drivers/Src/adc_sequence_driver.c Drivers/User\ Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F070xB -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I"../../User Drivers/Inc" -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/User Drivers/Src/adc_sequence_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/User\ Drivers/Src/button_driver.o: ../Drivers/User\ Drivers/Src/button_driver.c Drivers/User\ Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F070xB -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I"../../User Drivers/Inc" -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/User Drivers/Src/button_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/User\ Drivers/Src/button_exti_driver.o: ../Drivers/User\ Drivers/Src/button_exti_driver.c Drivers/User\ Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F070xB -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I"../../User Drivers/Inc" -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/User Drivers/Src/button_exti_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/User\ Drivers/Src/led_driver.o: ../Drivers/User\ Drivers/Src/led_driver.c Drivers/User\ Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F070xB -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I"../../User Drivers/Inc" -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/User Drivers/Src/led_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/User\ Drivers/Src/pwm_driver.o: ../Drivers/User\ Drivers/Src/pwm_driver.c Drivers/User\ Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F070xB -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I"../../User Drivers/Inc" -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/User Drivers/Src/pwm_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/User\ Drivers/Src/servo_driver.o: ../Drivers/User\ Drivers/Src/servo_driver.c Drivers/User\ Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F070xB -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I"../../User Drivers/Inc" -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/User Drivers/Src/servo_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/User\ Drivers/Src/timer14_driver.o: ../Drivers/User\ Drivers/Src/timer14_driver.c Drivers/User\ Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F070xB -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I"../../User Drivers/Inc" -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/User Drivers/Src/timer14_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/User\ Drivers/Src/timer6_driver.o: ../Drivers/User\ Drivers/Src/timer6_driver.c Drivers/User\ Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F070xB -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I"../../User Drivers/Inc" -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/User Drivers/Src/timer6_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/User\ Drivers/Src/uart_driver.o: ../Drivers/User\ Drivers/Src/uart_driver.c Drivers/User\ Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F070xB -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I"../../User Drivers/Inc" -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/User Drivers/Src/uart_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-User-20-Drivers-2f-Src

clean-Drivers-2f-User-20-Drivers-2f-Src:
	-$(RM) ./Drivers/User\ Drivers/Src/adc_int_driver.cyclo ./Drivers/User\ Drivers/Src/adc_int_driver.d ./Drivers/User\ Drivers/Src/adc_int_driver.o ./Drivers/User\ Drivers/Src/adc_int_driver.su ./Drivers/User\ Drivers/Src/adc_sequence_driver.cyclo ./Drivers/User\ Drivers/Src/adc_sequence_driver.d ./Drivers/User\ Drivers/Src/adc_sequence_driver.o ./Drivers/User\ Drivers/Src/adc_sequence_driver.su ./Drivers/User\ Drivers/Src/button_driver.cyclo ./Drivers/User\ Drivers/Src/button_driver.d ./Drivers/User\ Drivers/Src/button_driver.o ./Drivers/User\ Drivers/Src/button_driver.su ./Drivers/User\ Drivers/Src/button_exti_driver.cyclo ./Drivers/User\ Drivers/Src/button_exti_driver.d ./Drivers/User\ Drivers/Src/button_exti_driver.o ./Drivers/User\ Drivers/Src/button_exti_driver.su ./Drivers/User\ Drivers/Src/led_driver.cyclo ./Drivers/User\ Drivers/Src/led_driver.d ./Drivers/User\ Drivers/Src/led_driver.o ./Drivers/User\ Drivers/Src/led_driver.su ./Drivers/User\ Drivers/Src/pwm_driver.cyclo ./Drivers/User\ Drivers/Src/pwm_driver.d ./Drivers/User\ Drivers/Src/pwm_driver.o ./Drivers/User\ Drivers/Src/pwm_driver.su ./Drivers/User\ Drivers/Src/servo_driver.cyclo ./Drivers/User\ Drivers/Src/servo_driver.d ./Drivers/User\ Drivers/Src/servo_driver.o ./Drivers/User\ Drivers/Src/servo_driver.su ./Drivers/User\ Drivers/Src/timer14_driver.cyclo ./Drivers/User\ Drivers/Src/timer14_driver.d ./Drivers/User\ Drivers/Src/timer14_driver.o ./Drivers/User\ Drivers/Src/timer14_driver.su ./Drivers/User\ Drivers/Src/timer6_driver.cyclo ./Drivers/User\ Drivers/Src/timer6_driver.d ./Drivers/User\ Drivers/Src/timer6_driver.o ./Drivers/User\ Drivers/Src/timer6_driver.su ./Drivers/User\ Drivers/Src/uart_driver.cyclo ./Drivers/User\ Drivers/Src/uart_driver.d ./Drivers/User\ Drivers/Src/uart_driver.o ./Drivers/User\ Drivers/Src/uart_driver.su

.PHONY: clean-Drivers-2f-User-20-Drivers-2f-Src

