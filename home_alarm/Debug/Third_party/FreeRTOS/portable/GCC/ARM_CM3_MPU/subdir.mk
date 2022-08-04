################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Third_party/FreeRTOS/portable/GCC/ARM_CM3_MPU/port.c 

OBJS += \
./Third_party/FreeRTOS/portable/GCC/ARM_CM3_MPU/port.o 

C_DEPS += \
./Third_party/FreeRTOS/portable/GCC/ARM_CM3_MPU/port.d 


# Each subdirectory must supply rules for building sources it contributes
Third_party/FreeRTOS/portable/GCC/ARM_CM3_MPU/%.o Third_party/FreeRTOS/portable/GCC/ARM_CM3_MPU/%.su: ../Third_party/FreeRTOS/portable/GCC/ARM_CM3_MPU/%.c Third_party/FreeRTOS/portable/GCC/ARM_CM3_MPU/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xBA -c -I../Core/Inc -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/Third_party/FreeRTOS" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/Third_party/FreeRTOS/portable/GCC/ARM_CM3" -I"C:/Users/papai/Documents/cubeide/alarm_workspace/home_alarm/Third_party/FreeRTOS/include" -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Third_party-2f-FreeRTOS-2f-portable-2f-GCC-2f-ARM_CM3_MPU

clean-Third_party-2f-FreeRTOS-2f-portable-2f-GCC-2f-ARM_CM3_MPU:
	-$(RM) ./Third_party/FreeRTOS/portable/GCC/ARM_CM3_MPU/port.d ./Third_party/FreeRTOS/portable/GCC/ARM_CM3_MPU/port.o ./Third_party/FreeRTOS/portable/GCC/ARM_CM3_MPU/port.su

.PHONY: clean-Third_party-2f-FreeRTOS-2f-portable-2f-GCC-2f-ARM_CM3_MPU

