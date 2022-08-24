################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/adc.c \
../Core/Src/dma.c \
../Core/Src/gpio.c \
../Core/Src/i2c.c \
../Core/Src/main.c \
../Core/Src/spi.c \
../Core/Src/stm32l1xx_hal_msp.c \
../Core/Src/stm32l1xx_hal_timebase_tim.c \
../Core/Src/stm32l1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l1xx.c \
../Core/Src/tim.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/adc.o \
./Core/Src/dma.o \
./Core/Src/gpio.o \
./Core/Src/i2c.o \
./Core/Src/main.o \
./Core/Src/spi.o \
./Core/Src/stm32l1xx_hal_msp.o \
./Core/Src/stm32l1xx_hal_timebase_tim.o \
./Core/Src/stm32l1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l1xx.o \
./Core/Src/tim.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/adc.d \
./Core/Src/dma.d \
./Core/Src/gpio.d \
./Core/Src/i2c.d \
./Core/Src/main.d \
./Core/Src/spi.d \
./Core/Src/stm32l1xx_hal_msp.d \
./Core/Src/stm32l1xx_hal_timebase_tim.d \
./Core/Src/stm32l1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l1xx.d \
./Core/Src/tim.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xBA -c -I../Core/Inc -I"C:/repos/private/FW/home_alarm_fw/home_alarm/Third_party/FreeRTOS" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/Third_party/FreeRTOS/portable/GCC/ARM_CM3" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/Third_party/FreeRTOS/include" -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/tasks/core_tasks/init_task" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/tasks/core_tasks/manager_task" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/tasks/core_tasks/uart_task" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/tasks/gsm_task" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/tasks/io_task" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/tasks/lcd_task" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/tasks/numpad_task" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/libs/lcd_lib" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/libs/numpad_lib" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/interface" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/libs/circbuffer_lib" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/libs/M66_lib" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/libs/config_lib" -I"C:/repos/private/FW/home_alarm_fw/home_alarm/app/libs/flash_lib" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/adc.d ./Core/Src/adc.o ./Core/Src/adc.su ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/stm32l1xx_hal_msp.d ./Core/Src/stm32l1xx_hal_msp.o ./Core/Src/stm32l1xx_hal_msp.su ./Core/Src/stm32l1xx_hal_timebase_tim.d ./Core/Src/stm32l1xx_hal_timebase_tim.o ./Core/Src/stm32l1xx_hal_timebase_tim.su ./Core/Src/stm32l1xx_it.d ./Core/Src/stm32l1xx_it.o ./Core/Src/stm32l1xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32l1xx.d ./Core/Src/system_stm32l1xx.o ./Core/Src/system_stm32l1xx.su ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

