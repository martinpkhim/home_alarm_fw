################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include app/tasks/numpad_task/subdir.mk
-include app/tasks/lcd_task/subdir.mk
-include app/tasks/io_task/subdir.mk
-include app/tasks/gsm_task/subdir.mk
-include app/tasks/core_tasks/manager_task/subdir.mk
-include app/tasks/core_tasks/init_task/subdir.mk
-include app/libs/numpad_lib/subdir.mk
-include app/libs/lcd_lib/subdir.mk
-include app/libs/config_lib/subdir.mk
-include app/libs/circbuffer_lib/subdir.mk
-include app/libs/M66_lib/subdir.mk
-include app/interface/subdir.mk
-include app/subdir.mk
-include Third_party/FreeRTOS/portable/MemMang/subdir.mk
-include Third_party/FreeRTOS/portable/GCC/ARM_CM3/subdir.mk
-include Third_party/FreeRTOS/subdir.mk
-include Drivers/STM32L1xx_HAL_Driver/Src/subdir.mk
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


BUILD_ARTIFACT_NAME := home_alarm
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
home_alarm.elf \

MAP_FILES += \
home_alarm.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
home_alarm.list \

OBJCOPY_HEX += \
home_alarm.hex \

OBJCOPY_BIN += \
home_alarm.bin \


# All Target
all: main-build

# Main-build Target
main-build: home_alarm.elf secondary-outputs

# Tool invocations
home_alarm.elf home_alarm.map: $(OBJS) $(USER_OBJS) C:\repos\private\FW\home_alarm_fw\home_alarm\STM32L152C6TXA_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "home_alarm.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\repos\private\FW\home_alarm_fw\home_alarm\STM32L152C6TXA_FLASH.ld" --specs=nosys.specs -Wl,-Map="home_alarm.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

home_alarm.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "home_alarm.list"
	@echo 'Finished building: $@'
	@echo ' '

home_alarm.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "home_alarm.hex"
	@echo 'Finished building: $@'
	@echo ' '

home_alarm.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "home_alarm.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout home_alarm.bin home_alarm.elf home_alarm.hex home_alarm.list home_alarm.map
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
