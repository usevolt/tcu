################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hal/uv_hal/freertos/portable/Common/mpu_wrappers.c 

OBJS += \
./hal/uv_hal/freertos/portable/Common/mpu_wrappers.o 

C_DEPS += \
./hal/uv_hal/freertos/portable/Common/mpu_wrappers.d 


# Each subdirectory must supply rules for building sources it contributes
hal/uv_hal/freertos/portable/Common/%.o: ../hal/uv_hal/freertos/portable/Common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


