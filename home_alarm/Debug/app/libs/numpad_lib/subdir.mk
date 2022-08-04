################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app/libs/numpad_lib/numpad.c 

OBJS += \
./app/libs/numpad_lib/numpad.o 

C_DEPS += \
./app/libs/numpad_lib/numpad.d 


# Each subdirectory must supply rules for building sources it contributes
app/libs/numpad_lib/%.o app/libs/numpad_lib/%.su: ../app/libs/numpad_lib/%.c app/libs/numpad_lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xBA -c -I../Core/Inc -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/Third_party/FreeRTOS" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/Third_party/FreeRTOS/portable/GCC/ARM_CM3" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/Third_party/FreeRTOS/include" -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/app" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/app/tasks/core_tasks/init_task" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/app/tasks/core_tasks/manager_task" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/app/tasks/core_tasks/uart_task" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/app/tasks/gsm_task" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/app/tasks/io_task" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/app/tasks/lcd_task" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/app/tasks/numpad_task" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/app/libs/lcd_lib" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/app/libs/numpad_lib" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/app/interface" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-app-2f-libs-2f-numpad_lib

clean-app-2f-libs-2f-numpad_lib:
	-$(RM) ./app/libs/numpad_lib/numpad.d ./app/libs/numpad_lib/numpad.o ./app/libs/numpad_lib/numpad.su

.PHONY: clean-app-2f-libs-2f-numpad_lib

