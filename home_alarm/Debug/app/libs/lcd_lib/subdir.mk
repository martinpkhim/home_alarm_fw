################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app/libs/lcd_lib/lcd.c 

OBJS += \
./app/libs/lcd_lib/lcd.o 

C_DEPS += \
./app/libs/lcd_lib/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
app/libs/lcd_lib/%.o app/libs/lcd_lib/%.su: ../app/libs/lcd_lib/%.c app/libs/lcd_lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xBA -c -I../Core/Inc -I"C:/repos/private/FW/home_alarm_fw/home_alarm/Third_party/FreeRTOS" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/Third_party/FreeRTOS/portable/GCC/ARM_CM3" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/Third_party/FreeRTOS/include" -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/tasks/core_tasks/init_task" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/tasks/core_tasks/manager_task" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/tasks/core_tasks/uart_task" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/tasks/gsm_task" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/tasks/io_task" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/tasks/lcd_task" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/tasks/numpad_task" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/libs/lcd_lib" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/libs/numpad_lib" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/interface" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/libs/circbuffer_lib" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/libs/M66_lib" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/libs/config_lib" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/libs/flash_lib" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-app-2f-libs-2f-lcd_lib

clean-app-2f-libs-2f-lcd_lib:
	-$(RM) ./app/libs/lcd_lib/lcd.d ./app/libs/lcd_lib/lcd.o ./app/libs/lcd_lib/lcd.su

.PHONY: clean-app-2f-libs-2f-lcd_lib

