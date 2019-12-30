################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hal/CMSIS_CORE_LPC11xx/src/cr_startup_lpc11xx.c \
../hal/CMSIS_CORE_LPC11xx/src/system_LPC11xx.c 

OBJS += \
./hal/CMSIS_CORE_LPC11xx/src/cr_startup_lpc11xx.o \
./hal/CMSIS_CORE_LPC11xx/src/system_LPC11xx.o 

C_DEPS += \
./hal/CMSIS_CORE_LPC11xx/src/cr_startup_lpc11xx.d \
./hal/CMSIS_CORE_LPC11xx/src/system_LPC11xx.d 


# Each subdirectory must supply rules for building sources it contributes
hal/CMSIS_CORE_LPC11xx/src/%.o: ../hal/CMSIS_CORE_LPC11xx/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


