################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Third_party/FreeRTOS/croutine.c \
../Third_party/FreeRTOS/event_groups.c \
../Third_party/FreeRTOS/list.c \
../Third_party/FreeRTOS/queue.c \
../Third_party/FreeRTOS/stream_buffer.c \
../Third_party/FreeRTOS/tasks.c \
../Third_party/FreeRTOS/timers.c 

OBJS += \
./Third_party/FreeRTOS/croutine.o \
./Third_party/FreeRTOS/event_groups.o \
./Third_party/FreeRTOS/list.o \
./Third_party/FreeRTOS/queue.o \
./Third_party/FreeRTOS/stream_buffer.o \
./Third_party/FreeRTOS/tasks.o \
./Third_party/FreeRTOS/timers.o 

C_DEPS += \
./Third_party/FreeRTOS/croutine.d \
./Third_party/FreeRTOS/event_groups.d \
./Third_party/FreeRTOS/list.d \
./Third_party/FreeRTOS/queue.d \
./Third_party/FreeRTOS/stream_buffer.d \
./Third_party/FreeRTOS/tasks.d \
./Third_party/FreeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Third_party/FreeRTOS/%.o Third_party/FreeRTOS/%.su: ../Third_party/FreeRTOS/%.c Third_party/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xBA -c -I../Core/Inc -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/Third_party/FreeRTOS" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/Third_party/FreeRTOS/portable/GCC/ARM_CM3" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/Third_party/FreeRTOS/include" -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/app" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/app/tasks/core_tasks/init_task" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/app/tasks/core_tasks/manager_task" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/app/tasks/core_tasks/uart_task" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/app/tasks/gsm_task" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/app/tasks/io_task" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/app/tasks/lcd_task" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/app/tasks/numpad_task" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/app/libs/lcd_lib" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/app/libs/numpad_lib" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/app/interface" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Third_party-2f-FreeRTOS

clean-Third_party-2f-FreeRTOS:
	-$(RM) ./Third_party/FreeRTOS/croutine.d ./Third_party/FreeRTOS/croutine.o ./Third_party/FreeRTOS/croutine.su ./Third_party/FreeRTOS/event_groups.d ./Third_party/FreeRTOS/event_groups.o ./Third_party/FreeRTOS/event_groups.su ./Third_party/FreeRTOS/list.d ./Third_party/FreeRTOS/list.o ./Third_party/FreeRTOS/list.su ./Third_party/FreeRTOS/queue.d ./Third_party/FreeRTOS/queue.o ./Third_party/FreeRTOS/queue.su ./Third_party/FreeRTOS/stream_buffer.d ./Third_party/FreeRTOS/stream_buffer.o ./Third_party/FreeRTOS/stream_buffer.su ./Third_party/FreeRTOS/tasks.d ./Third_party/FreeRTOS/tasks.o ./Third_party/FreeRTOS/tasks.su ./Third_party/FreeRTOS/timers.d ./Third_party/FreeRTOS/timers.o ./Third_party/FreeRTOS/timers.su

.PHONY: clean-Third_party-2f-FreeRTOS

