################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include release/src/subdir.mk
-include release/hal/uv_hal/src_lpc1549/subdir.mk
-include release/hal/uv_hal/src/output/subdir.mk
-include release/hal/uv_hal/src/canopen/subdir.mk
-include release/hal/uv_hal/src/subdir.mk
-include release/hal/uv_hal/freertos/portable/GCC/ARM_CM3/subdir.mk
-include release/hal/uv_hal/freertos/subdir.mk
-include release/hal/lpc_chip_15xx/src/subdir.mk
-include hal/uv_hal/src_lpc1785/subdir.mk
-include hal/uv_hal/src_lpc1549/subdir.mk
-include hal/uv_hal/src_linux/subdir.mk
-include hal/uv_hal/src/ui/subdir.mk
-include hal/uv_hal/src/output/subdir.mk
-include hal/uv_hal/src/canopen/subdir.mk
-include hal/uv_hal/src/subdir.mk
-include hal/uv_hal/freertos/portable/GCC/Posix/subdir.mk
-include hal/uv_hal/freertos/portable/GCC/ARM_CM3_MPU/subdir.mk
-include hal/uv_hal/freertos/portable/GCC/ARM_CM3/subdir.mk
-include hal/uv_hal/freertos/portable/GCC/ARM_CM0/subdir.mk
-include hal/uv_hal/freertos/portable/Common/subdir.mk
-include hal/uv_hal/freertos/subdir.mk
-include hal/lpc_chip_15xx/src/subdir.mk
-include hal/lpc_chip_15xx/Debug/src/subdir.mk
-include hal/CMSIS_CORE_LPC177x_8x/src/subdir.mk
-include hal/CMSIS_CORE_LPC11xx/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: hcu

# Tool invocations
hcu: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Linker'
	gcc  -o "hcu" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) hcu
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
