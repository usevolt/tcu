################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hal/CMSIS_CORE_LPC177x_8x/src/system_LPC177x_8x.c 

OBJS += \
./hal/CMSIS_CORE_LPC177x_8x/src/system_LPC177x_8x.o 

C_DEPS += \
./hal/CMSIS_CORE_LPC177x_8x/src/system_LPC177x_8x.d 


# Each subdirectory must supply rules for building sources it contributes
hal/CMSIS_CORE_LPC177x_8x/src/%.o: ../hal/CMSIS_CORE_LPC177x_8x/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


