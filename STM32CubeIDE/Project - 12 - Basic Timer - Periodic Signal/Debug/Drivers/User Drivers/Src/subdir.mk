################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/temp/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User\ Drivers/Src/button_driver.c \
D:/temp/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User\ Drivers/Src/led_driver.c \
D:/temp/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User\ Drivers/Src/pwm_driver.c \
D:/temp/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User\ Drivers/Src/servo_driver.c \
D:/temp/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User\ Drivers/Src/timer14_driver.c \
D:/temp/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User\ Drivers/Src/timer6_driver.c \
D:/temp/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User\ Drivers/Src/uart_driver.c 

OBJS += \
./Drivers/User\ Drivers/Src/button_driver.o \
./Drivers/User\ Drivers/Src/led_driver.o \
./Drivers/User\ Drivers/Src/pwm_driver.o \
./Drivers/User\ Drivers/Src/servo_driver.o \
./Drivers/User\ Drivers/Src/timer14_driver.o \
./Drivers/User\ Drivers/Src/timer6_driver.o \
./Drivers/User\ Drivers/Src/uart_driver.o 

C_DEPS += \
./Drivers/User\ Drivers/Src/button_driver.d \
./Drivers/User\ Drivers/Src/led_driver.d \
./Drivers/User\ Drivers/Src/pwm_driver.d \
./Drivers/User\ Drivers/Src/servo_driver.d \
./Drivers/User\ Drivers/Src/timer14_driver.d \
./Drivers/User\ Drivers/Src/timer6_driver.d \
./Drivers/User\ Drivers/Src/uart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/User\ Drivers/Src/button_driver.o: D:/temp/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User\ Drivers/Src/button_driver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F070xB -DUSE_HAL_DRIVER -DDEBUG -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I"D:/temp/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User Drivers/Inc" -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/User Drivers/Src/button_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/User\ Drivers/Src/led_driver.o: D:/temp/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User\ Drivers/Src/led_driver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F070xB -DUSE_HAL_DRIVER -DDEBUG -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I"D:/temp/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User Drivers/Inc" -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/User Drivers/Src/led_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/User\ Drivers/Src/pwm_driver.o: D:/temp/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User\ Drivers/Src/pwm_driver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F070xB -DUSE_HAL_DRIVER -DDEBUG -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I"D:/temp/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User Drivers/Inc" -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/User Drivers/Src/pwm_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/User\ Drivers/Src/servo_driver.o: D:/temp/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User\ Drivers/Src/servo_driver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F070xB -DUSE_HAL_DRIVER -DDEBUG -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I"D:/temp/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User Drivers/Inc" -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/User Drivers/Src/servo_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/User\ Drivers/Src/timer14_driver.o: D:/temp/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User\ Drivers/Src/timer14_driver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F070xB -DUSE_HAL_DRIVER -DDEBUG -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I"D:/temp/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User Drivers/Inc" -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/User Drivers/Src/timer14_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/User\ Drivers/Src/timer6_driver.o: D:/temp/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User\ Drivers/Src/timer6_driver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F070xB -DUSE_HAL_DRIVER -DDEBUG -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I"D:/temp/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User Drivers/Inc" -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/User Drivers/Src/timer6_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/User\ Drivers/Src/uart_driver.o: D:/temp/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User\ Drivers/Src/uart_driver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F070xB -DUSE_HAL_DRIVER -DDEBUG -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I"D:/temp/STM32TrainingExamplesRegisterLevel/STM32CubeIDE/User Drivers/Inc" -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/User Drivers/Src/uart_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

